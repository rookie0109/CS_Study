# PPO
[ICLR2022 blog](https://ppo-details.cleanrl.dev//2021/11/05/ppo-implementation-details/)
## 13 Core implementation
1. 矢量化结构 vectorized architecture

使用一个learner 在多个环境中采样，具体而言，PPO初始化矢量化环境，堆叠N个子环境成一个环境。之后矢量化结构循环两个阶段：rollout phase(learn接受N个观测和采样的N个动作)
N个子环境，M是步数，N*M表示在训练中使用的固定长度的轨迹段。
N是num_envs(决策C1)和M * N 是中的iteration_size(决策C2)，他们建议增加N(如N=256)
提高了训练吞吐量，但使性能变差。他们认为，性能下降是由于“缩短的经验块”(M由于N的增加而变小
在他们的设置中)和“早期值引导”。
2. 权值的正交初始化和偏置的常数初始化
权重的正交初始化(torch.nn.init.orthogonal_).即使得权重矩阵的转置与原矩阵的乘积是一个对角矩阵。正交矩阵的特点是其转置和逆矩阵相等，因此在初始化时，这种方法有助于避免梯度消失或梯度爆炸的问题。
一般情况下，隐层的权重使用比例为np.sqrt(2)的正交权重初始化，偏差设为0。但是，策略输出层权重初始化的尺度为0.01。值输出层权重初始化为1的比例。有人发现正交权重相较于Xavier初始化效果更好。而且Andrychowicz等人(2021)发现将动作分布集中在0附近(即以0.01”初始化策略输出层权重)是有益的。
3. The Adam Optimizer’s Epsilon Parameter
PPO sets the epsilon parameter to 1e-5
4. Adam Learning Rate Annealing
训练玩Atari游戏的代理的超参数将学习率设置为随着时间步数的增加从2.5e-4线性衰减到0。在MuJoCo中，学习率从3e-4线性衰减到0。
5. Generalized Advantage Estimation
6. mini_batch Updates

在向量化体系结构的学习阶段，PPO实现对大小为N * M的训练数据的索引进行完全洗刷并将其分成小批来计算梯度并更新策略。
7. Normalization of Advantages
在基于GAE计算优势后，PPO通过减去优势的平均值并除以优势的标准差对优势进行归一化。特别是，这种规范化发生在小批级别，而不是整个批级别!
Andrychowicz等人(2021)(决策C67)发现每小批量优势归一化不会对性能产生太大影响(图35)。
8. clip sorrogate objective
Engstrom, Ilyas等人(2020)发现，当他们控制其他实施细节相同时，PPO的剪切目标与TRPO的目标具有相似的性能。Andrychowicz等人(2021)发现PPO的裁剪目标在大多数任务中优于香草策略梯度(PG)、V-trace、AWR和V-MPO (Espeholt等人，2018)。
基于上述发现，我们认为PPO的裁剪目标仍然是一个伟大的目标，因为它实现了与TRPO的目标相似的性能，同时计算成本更低(即不需要像TR那样进行二阶优化)
9. Value Function Loss Clipping
Engstrom, Ilyas等人(2020)没有发现价值函数损失裁剪有助于提高性能的证据。Andrychowicz等人(2021)认为，价值函数损失裁剪甚至会损害性能(决策C13，图43)。
我们实现了这个细节，因为这项工作更多的是关于先前结果的高保真再现。
10. Overall Loss and Entropy Bonus 
总的损失计算为loss = policy_loss - entropy * entropy_coefficient + value_loss * value_coefficient，这使熵奖励项最大化。请注意，策略参数和值参数共享相同的优化器。
Mnih等人报告说，通过鼓励行动概率分布更加随机，这种熵奖励可以改善探索。
Andrychowicz等人(2021)总体上没有发现熵项在连续控制环境下提高性能的证据(决策C13，图76和图77)。
11. Global Gradient Clipping
对于一个历元中的每次更新迭代，PPO重新缩放策略和值网络的梯度，使“全局l2范数”(即所有参数的梯度连接的范数)不超过0.5。
Andrychowicz等人(2021)发现全局梯度裁剪可以提供一个小的性能提升(决策C68，图34)。
12. debug variables
Policy_loss:所有数据点上的平均策略损失。
Value_loss:所有数据点的平均值损失。
Entropy_loss:所有数据点的平均熵值。
clifrrac:触发被剪辑目标的训练数据的部分。
approxkl:近似Kullback-Leibler散度，由(-logratio).mean()测量，对应于John Schulman关于近似KL散度的博文中的k1估计量。这篇博文还建议使用另一种估计器((ratio - 1) - logratio).mean()，它是无偏的，方差较小。
13. Shared and separate MLP networks for policy and value functions
一般而言较为简单的环境中separate的效果更好

## 连续领域的相关细节

1. 通过正态分布进行连续操作
策略梯度方法（包括 PPO）假设连续动作是从正态分布中采样的。因此，要创建这样的分布，神经网络需要输出连续动作的平均值和标准差。
输出时：确定输出或者随机采样
```python
    @abstractmethod
    def sample(self) -> th.Tensor:
        """
        Returns a sample from the probability distribution

        :return: the stochastic action
        """

    @abstractmethod
    def mode(self) -> th.Tensor:
        """
        Returns the most likely action (deterministic output)
        from the probability distribution

        :return: the stochastic action
        """

    def get_actions(self, deterministic: bool = False) -> th.Tensor:
        """
        Return actions according to the probability distribution.

        :param deterministic:
        :return:
        """
        if deterministic:
            return self.mode()
        return self.sample()
```
2. 与状态无关的对数标准差

该实现输出均值的对数，但不是输出标准差的对数，而是输出标准的对数偏差。另外，这个log std被设置为状态无关并初始化为0。
3. Independent action components 
独立的输出维度，比如机器人的线速度和角速度是两个独立的变量。
这种方法来自于目前常用的假设:使用全协方差的高斯分布来表示策略，这意味着每个维度的动作选择是独立执行的。Tavakoli等(2018)在面对多维行动空间环境时，也认为每个行动维度都应该独立选择，并通过设计网络结构来实现这一目标。虽然我们的直觉告诉我们，在某些环境中，不同政策维度的行动选择之间可能存在依赖关系，但什么是最优选择仍然是一个悬而未决的问题。值得注意的是，这个问题已经引起了社区的关注，并开始尝试在不同维度上对行为的依赖关系进行建模，例如使用自回归策略(Metz等人(2019)，Zhang等人(2019))。
4. Separate MLP networks for policy and value functions

Andrychowicz等人(2021)发现，独立的政策和价值网络通常会带来更好的绩效(决策C47，图15)。
5. Handling of action clipping to valid range and storage 处理动作剪辑到有效范围和存储

由于高斯分布的抽样是没有边界的，所以环境通常对动作空间有一定的限制。因此Duan et al.(2016)采用将采样动作裁剪到其边界内，Haarnoja et al.(2018)对高斯样本采用可逆压碎函数(tanh)来满足约束。Andrychowicz等人(2021)比较了两种实现方法，发现tanh方法更好(decision C63，图17)。但是为了获得一致的性能，我们选择了clip的实现。值得注意的是，Chou 2017和Fujita等人(2018)指出了clip方法带来的偏差，并提出了不同的解决方案。
```python
# Clip the actions to avoid out of bound error
if isinstance(self.action_space, gym.spaces.Box):
    clipped_actions = np.clip(actions, self.action_space.low, self.action_space.high)
```

6. Normalization of Observation

在每个时间步，VecNormalize 包装器都会对观察结果进行预处理，然后将其提供给 PPO 代理。通过减去其运行平均值并除以其方差来对原始观察值进行归一化。
在输入上使用归一化已经成为一种众所周知的训练神经网络的技术。Duan等人(2016)对观测值采用移动平均归一化处理网络的输入，这也成为后续实现的默认选择。Andrychowicz等人(2021)通过实验确定，观察归一化对性能非常有帮助(决策C64，图33)。
7. Observation Clipping

Andrychowicz等人(2021)发现，在观测归一化后，使用观测剪辑对性能没有帮助(decision C65，图38)，但猜测在观测范围较大的环境下可能会有所帮助。
8. Reward Scaling 
非常有用， self.returns = self.returns * self.gamma + reward
9.  Reward Clipping

效果不大

## 4个辅助技巧
1. Clip Range Annealing
PPO 的裁剪系数可以像学习率衰减一样进行衰减
2. Parallellized Gradient Update

策略梯度采用多进程并行计算，主要用于ppo1，ppo2默认不使用。这样的范例可以通过利用所有可用的流程来缩短培训时间。
3. Early Stopping of the policy optimizations 

它首先跟踪网络权重的一个更新步骤之前和之后策略之间的近似平均 KL 散度。如果所述KL散度超过预设阈值，则抢先停止策略权重的更新。
4. Invalid Action Masking
无效动作屏蔽是 AlphaStar (Vinyals et al., 2019) 和 OpenAI Five () 中最常用的一种技术Berner 等人，2019），以避免在使用策略梯度算法训练代理时在给定的游戏状态下执行无效操作。具体来说，无效动作屏蔽是通过在将 logits 传递给 softmax 之前将与无效动作对应的 logits 替换为负无穷大来实现的。 Huang and Ontañón，2020展示了这样的范式实际上使无效动作对应的梯度为零< a i=8>.此外，Huang 等人，2021 证明无效动作屏蔽是训练代理战胜他们测试的所有过去的 μRTS 机器人的关键技术。
在我们的复现过程中，我们发现了一些有用的调试技巧，具体如下：

1. 随机种子：一种调试方法是对所有操作进行随机种子设置，然后观察何时与参考实现开始产生差异。因此，您可以为您的实现和我们的实现使用相同的种子，检查环境返回的观测是否相同，然后检查采样的动作是否相同。通过按照这些步骤进行检查，您可以确保所有内容都是对齐的（例如，打印出 values.sum() 并检查是否与参考实现匹配）。在过去，我们曾在 pytorch-a2c-ppo-acktr-gail 存储库上使用过这种方法，最终找出了我们实现中的错误。

2. 检查 ratio 是否等于1：在第一个时期和第一个小批量更新期间检查 ratio 是否始终为1，此时新旧策略相同，因此 ratio 为1，没有需要剪切的内容。如果 ratio 不为1，这意味着存在错误，程序未重新构建用于回放的概率分布。

3. 检查 Kullback-Leibler（KL）散度：通常检查 KL 散度是否过高是很有用的。我们通常发现 approx_kl 保持在0.02以下，如果 approx_kl 变得过高，通常意味着策略变化过快，存在错误。

4. 检查其他指标：正如结果部分所示，我们实现中的其他指标（如策略和价值损失）也与原始实现非常相似。因此，如果您的策略损失曲线看起来与参考实现非常不同，可能存在错误。

5. 经验法则：在打砖块游戏中获得400的回合累积奖励是一种检查 PPO 性能的实用经验法则。我们发现这是一个实用的经验法则，用于评估 GitHub 上在线 PPO 实现的可靠性。通常我们发现 PPO 存储库无法达到这个标准，因此我们知道它们可能与 openai/baselines 的 PPO 的所有实现细节不完全一致。


## 并行
在5分钟内使用PPO + Envpool解决Pong

## 后续研究
鉴于这篇博文，我们相信社区对于PPO有了更深的理解，并且将更有可能进行改进。以下是一些建议的研究方向。

1. 替代选择：在深入研究了PPO的不同细节后，似乎其中一些结果是由于任意选择造成的。有趣的是调查替代选择，并看看这种改变如何影响结果。以下是一些可以探索的非详尽列表：
   - 使用不同的Atari预处理（正如Machado等人部分探索的那样）
   - 对于连续动作使用不同的分布（Beta分布、压缩的高斯、具有完整协方差的高斯等），这很可能需要一些调整
   - 在使用连续动作时，使用状态相关的标准差（是否将梯度反向传播到整个演员网络）
   - 使用不同的LSTM初始化（使用1而不是0，随机噪声，可学习参数等），使用GRU单元而不是LSTM

2. 基于经验回放的方法的矢量化架构：基于经验回放的方法，如DQN、DDPG和SAC，由于一些原因比PPO不太受欢迎：1）由于单一仿真环境通常具有较低的吞吐量（也意味着较低的GPU利用率），2）它们通常具有更高的内存需求（例如，DQN需要臭名昭著的100万样本回放缓冲区，可能需要32GB内存）。我们能否将矢量化架构应用于基于经验回放的方法？矢量化环境在直观上应该替代回放缓冲区，因为环境还可以提供不相关的经验。

3. 值函数优化：在Phasic Policy Gradient（Cobbe等人，2021）中，独立优化值函数被证明是重要的。在DQN中，优先级经验回放显著提升了性能。我们能否将优先级经验回放应用于PPO，或者仅应用于PPO的值函数？
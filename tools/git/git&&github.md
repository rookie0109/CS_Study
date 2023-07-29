# git && github记录
使用记录

## git

### 相关指令

```bash
# 下载仓库内容
git clone url

# 将本地内容上传到github

# 将项目重命名
git remote add origin https://github.com/rookie0109/CS_Study.git

git add .  # 将项目所有文件加到缓存区

git commit -m '注释'

git push -u origin main

```





### git remote

```bash
git remote：列出当前仓库中已配置的远程仓库。
git remote -v：列出当前仓库中已配置的远程仓库，并显示它们的 URL。
git remote add <remote_name> <remote_url>：添加一个新的远程仓库。指定一个远程仓库的名称和 URL，将其添加到当前仓库中。
git remote rename <old_name> <new_name>：将已配置的远程仓库重命名。
git remote remove <remote_name>：从当前仓库中删除指定的远程仓库。
git remote set-url <remote_name> <new_url>：修改指定远程仓库的 URL。
git remote show <remote_name>：显示指定远程仓库的详细信息，包括 URL 和跟踪分支。
```

### 保存密码

```bash
# 在.git/config文件中加入
[credential]
    helper = store
```





## github

### 新建仓库

- gitignore文件

放在根目录下，可以在其中选择在git 提交过程中忽略一些文件

常见语法：<font style=background:red>待办</font>

- 许可证

开源项目必备，其中MIT最为宽松，几乎没有限制，GPL较为严格。



### 删除仓库

`Settings`最下方'delet'







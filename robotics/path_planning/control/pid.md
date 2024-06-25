P : 加快误差为零；
I ：降低稳态误差
D: 减小震荡(延时和I造成的)
```cpp
double PIDController::Control(const double error, const double dt) {
  if (dt <= 0) {
    AWARN << "dt <= 0, will use the last output, dt: " << dt;
    return previous_output_;
  }
  double diff = 0;
  double output = 0;

  if (first_hit_) {
    first_hit_ = false;
  } else {
    diff = (error - previous_error_) / dt;
  }
  // integral hold
  if (!integrator_enabled_) {
    integral_ = 0;
  } else if (!integrator_hold_) {
    integral_ += error * dt * ki_;
    // apply Ki before integrating to avoid steps when change Ki at steady state
    if (integral_ > integrator_saturation_high_) {
      integral_ = integrator_saturation_high_;
      integrator_saturation_status_ = 1;
    } else if (integral_ < integrator_saturation_low_) {
      integral_ = integrator_saturation_low_;
      integrator_saturation_status_ = -1;
    } else {
      integrator_saturation_status_ = 0;
    }
  }
  previous_error_ = error;
  output = error * kp_ + integral_ + diff * kd_;  // Ki already applied
  previous_output_ = output;
  return output;
}
```
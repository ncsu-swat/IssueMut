unsigned long long GetTimeFromFrames(int);
unsigned long long GetMicroSeconds();

void DequeueEvent(unsigned frame) {
  long long frame_time = GetTimeFromFrames(frame);
  unsigned long long current_time = GetMicroSeconds();

  if (frame_time < current_time) {
    DequeueEvent(0);
  } else {
    DequeueEvent(frame_time - current_time);
  }
}
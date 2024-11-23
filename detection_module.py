import serial
import time
from picamera2 import Picamera2
import subprocess
from datetime import datetime

# Arduino와의 시리얼 통신 설정
ser = serial.Serial("/dev/ttyACM0", 9600, timeout=1)
time.sleep(2)

picam2 = Picamera2()

# 사진을 찍고 저장하는 함수
def capture_video():
    current_timenow = datetime.now().strftime("%y.%m.%d_%H.%M.%S")
    current_time = current_timenow
    video_filename = f"/home/a/mywork/video_{current_time}.mp4"
    picam2.start_and_record_video(video_filename, duration=15)
    print("촬영이 완료되었습니다.")
    time.sleep(5)

while True:
    if ser.in_waiting > 0:
        message = ser.readline().decode().strip()
        if message == "Motion Detected":
            print("움직임이 감지되었습니다! 동영상을 촬영합니다.")
            capture_video()
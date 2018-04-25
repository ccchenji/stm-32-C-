import sensor, image, time,pyb
from pyb import UART
uart = UART(3, 115200)

BLUE_LED_PIN = 3
thresholds = (40, 130)  #灰度值设置

ROI = (74,23,198,205) #开窗大小


sensor.reset() # 初始化摄像头
sensor.set_pixformat(sensor.GRAYSCALE) # 格式为 RGB565.
sensor.set_framesize(sensor.QVGA) # 使用 QQVGA 速度快一些
sensor.set_windowing(ROI)
sensor.skip_frames(10) # 跳过10帧，使新设置生效
sensor.set_auto_whitebal(False)


clock = time.clock() # 追踪帧率


while(True):
    clock.tick() # Track elapsed milliseconds between snapshots().
    img = sensor.snapshot() # 从感光芯片获得一张图像
    pyb.LED(BLUE_LED_PIN).on()
    blobs = img.find_blobs([thresholds],pixel_threshold=3,threshold=3)


    if blobs:
      for b in blobs:
          img.draw_rectangle(b[0:4])
          img.draw_cross(b[5], b[6])

    H_xAngle=b[5]>>8&0xffffffff
    L_xAngle=b[5]&0xffffffff
    H_yAngle=b[6]>>8&0xffffffff
    L_yAngle=b[6]&0xffffffff
    uart_buf = bytearray([0x41,0x42,L_xAngle,H_xAngle,L_yAngle,H_yAngle,0x0d,0x0a])
    uart.write(uart_buf)
    time.sleep(1)

   # print(clock.fps()) # 注意: 你的OpenMV连到电脑后帧率下降



    #print(b[5])
    #print(b[6])


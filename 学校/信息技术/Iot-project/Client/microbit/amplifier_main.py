import audio

def ConnectWifi(SSID, PASSWORD):
  while Obloq.connectWifi(SSID,PASSWORD,10000) != True:
    display.show(".")
  display.scroll(Obloq.ifconfig())
  Obloq.httpConfig(IP,PORT)

def Init():
  uart.init(baudrate=9600, bits=8, parity=None, stop=1, tx=pin2, rx=pin1)
  ConnectWifi(SSID, PASSWORD)

if __name__ == '__main__':
  Init()
  while (True):
    errno, resp = Obloq.get("/amp")
    if (resp == 404):
      sleep(1000)
      continue
    m = resp
    frames = []
    l = len(m)
    k = 0
    for i in range(l // 32 + 1):
      frame = audio.AudioFrame()
      for j in range(len(frame)):
        if (k >= len(m)): break
        frame[j] = m[k]
        k += 1
      frames.append(frame)
    audio.play(frames)

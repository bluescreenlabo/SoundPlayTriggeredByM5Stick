import sys
import serial
import findComByMAC
import commandMP3

# ---- 設定 ----
BAUDRATE = 115200
TIMEOUT = 1.0       # read timeout (秒)

def main():
    data = ""
    try:
        while True:
            data = ser.readline().decode('utf-8').strip()
            if (data != ""):
                commandMP3.commandPlay(data)
                data = ""

    except KeyboardInterrupt:
        print("終了します")
    finally:
        ser.close()

# main関数コール
if __name__ == "__main__":
    # 引数でMACアドレスをもらう
    macstr = "004b12c26eB2"
    if len(sys.argv) == 2:
        macstr = sys.argv[1]
    
    port = findComByMAC.findComByMAC(macstr)
    
    # みつけたポートをオープンしてみる
    try:
        ser = serial.Serial(port, BAUDRATE, timeout=TIMEOUT)
        print(f"監視開始: {port} @ {BAUDRATE}bps")
    except Exception as e:
        print("シリアルポートオープン失敗:", e)
        sys.exit(1)

    # 音声データを初期化
    commandMP3.init()

    main()
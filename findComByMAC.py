import serial.tools.list_ports

# MACアドレスを文字列で渡すと、Bluetoothシリアルでつながったポート名を返す
# ex.MAC address = 11:22:33:44:aa:bb
# findComByMAC("11223344aabb")
# 帰り値は文字列 Windowsなら "COM3"など。Linuxなら "/dev/ttyUSB0"など
def findComByMAC(targetMacAdr):
    ports = serial.tools.list_ports.comports()
    bluetooth_port = ""

    for port in ports:
        if targetMacAdr.lower() in port.hwid.lower():
            bluetooth_port = port.device
        
    return bluetooth_port

if __name__ == "__main__":
    port = findComByMAC("004b12c26eb2")
    print(port)

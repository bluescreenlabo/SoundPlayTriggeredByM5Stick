# M5StickC plus2 を振るとPCから音が鳴る
## 概要
- M5StickとPCをシリアル通信で接続
- M5Stickが動きを検出したらシリアル通信経由で文字列をPCに送信
- PCでは特定の文字列に対応した音声ファイルを再生

## M5Stickへファームを書き込む
### Arduino IDEへのESP32ボードの追加
- Arduino IDE を開き、[環境設定] を開く
- [追加のボードマネージャのURL] に以下を追加
<pre>https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json</pre>
- [OK] を押して設定を保存。

### Arduino IDEへのESP32ボードのインストール
- [ツール] → [ボード] → [ボードマネージャ] を開く
- esp32 を検索し、esp32 by Espressif Systems をインストール

### M5StickJumpフォルダ内のinoファイルを開き、コンパイル＆書き込み
M5StickJump フォルダ内はM5StickC plus2用のArduinoプロジェクトです。<br>
書き込み、実行するとLCDにBTMACアドレスが表示されます。<br>
この状態で、音を出したいPCとbluetoothペアリングします。ペアリングは解除しない限り初回のみの作業となります。<br>
M5Stickは各操作に対応した文字列を送信します。文字列は画面も表示します。<br>
| 操作 | 文字列 |
| ---- | ---- |
| 縦方向に振る | "J" |
| 表面ボタンを押す | "A" |
| 側面ボタンを押す | "B" |

## PCでPythonプログラムを実行
### 音声ファイルを用意
再生したい音声ファイルを用意します。pygameで再生可能なフォーマットに限ります。（wav, mp3など)<br>
用意したファイルはpyファイルのあるフォルダ以下に配置するとよい。<br>
用意したファイルはcommandMP3.py内で「サウンドの読み込み」のコメントに従って読み込むようpythonコードを適宜修正してください<br>

### PCに必要なpythonライブラリをインストール
以下が必要です。
pyserial
pygame

### mp3test.pyを実行
MACアドレスを指定する必要があります。以下どちらかの方法で指定してください。
- メイン関数先頭の macstr変数を、M5Stickの画面に表示されているMACアドレスに置き換える
- 実行時にMACアドレスを指定する
<pre>python mp3test.py 112233445566</pre>
受信した文字列に対応したサウンドを再生します。詳細はcommandMP3.pyを読んでください。

### pythonファイルの説明
| ファイル | 説明 |
| ---- | ---- |
| mp3test.py | メイン関数。COMポートをオープン、文字列の取得待ち、取得した文字列を再生関数に渡す |
| commandMP3.py | 文字列を受け取り、対応した音源ファイルを再生 |
| findComByMAC.py | 与えられたMACアドレスを含むCOMポートを見つける（Windows用) |

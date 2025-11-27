# M5StickC plus2 を振るとPCから音が鳴る
## 概要
- M5StickとPCをシリアル通信で接続
- M5Stickが動きを検出したらシリアル通信経由で文字列をPCに送信
- PCでは特定の文字列に対応した音声ファイルを再生

## M5Stickへファームを書き込む
M5StickJump フォルダ内はM5StickC plus2用のArduinoプロジェクトです。<br>
書き込み、実行するとLCDにBTMACアドレスが表示されます。<br>
この状態で、音を出したいPCとbluetoothペアリングします。ペアリングは解除しない限り初回のみの作業となります。<br>

## PCでPythonプログラムを実行
### 音声ファイルを用意
再生したい音声ファイルを用意します。pygameで再生可能なフォーマットに限ります。（wav, mp3など)<br>





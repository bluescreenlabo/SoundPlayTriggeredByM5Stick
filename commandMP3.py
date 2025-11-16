import os
import pygame
import time

def init():
    global sound1
    global sound2
    global sound3
    global sound4
    global m_mistake

    # 実行中のスクリプトの絶対パスを取得
    absolute_path = os.path.abspath(__file__)
    directory_name = os.path.dirname(absolute_path)

    # サウンド再生のためpygameを初期化
    pygame.init()

    # サウンドの読み込み
    sound1 = pygame.mixer.Sound(directory_name + "\\data\\jump.mp3")
    sound2 = pygame.mixer.Sound(directory_name + "\\data\\coin.mp3")
    sound3 = pygame.mixer.Sound(directory_name + "\\data\\mistake.mp3")
    sound4 = pygame.mixer.Sound(directory_name + "\\data\\gameover.mp3")

    m_mistake = 0


# dataで受け取った文字列に対応した音を再生
def commandPlay(data):
    global sound1
    global sound2
    global sound3
    global sound4
    global m_mistake

    if "J" in data:
        if not pygame.mixer.get_busy():
            print(f"検出: '{"J"}'")
            sound1.play()

    if "A" in data:
        if not pygame.mixer.get_busy():
            print(f"検出: '{"A"}'")
            sound2.play()

    if "B" in data:
        if not pygame.mixer.get_busy():
            print(f"検出: '{"B"}'")
            if (m_mistake > 2):
                sound4.play()
                m_mistake = 0
            else:
                sound3.play()
                m_mistake += 1

# main関数コール
if __name__ == "__main__":
    init()
    commandPlay("A")
    time.sleep(10)

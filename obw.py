import time
import numpy as np

class Wsp:
    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y

    def set_x(self, x):
        self.x = x

    def set_y(self, y):
        self.y = y

    def get_x(self):
        return self.x

    def get_y(self):
        return self.y

def main():
    begin = time.time()

    try:
        with open("dane.txt", "r") as dane:
            rozmiar = int(dane.readline())

            if rozmiar < 3:
                raise ValueError("Error: za mało punktów")

            w = []
            for _ in range(rozmiar):
                x, y = map(float, dane.readline().split())
                w.append(Wsp(x, y))

    except FileNotFoundError:
        print("Error opening the file!")
        return

    # sortowanie po osi y rosnąco, od dołu do góry
    w.sort(key=lambda point: point.get_y())

    for point in w:
        print(f"{point.get_x()}  {point.get_y()}")

    # obwód dolny ułożony współzegarowo
    obw_D = []
    bottom = 0
    obw_D.append(w[0])
    for i in range(1, rozmiar):
        if w[i].get_x() <= obw_D[-1].get_x():
            obw_D.append(w[i])
        if w[i].get_x() > obw_D[0].get_x():
            obw_D.insert(0, w[i])
            bottom += 1

    print()
    for point in obw_D:
        print(f"{point.get_x()}  {point.get_y()}")
    print(f"bottom  {bottom}  {obw_D[bottom].get_x()}  {obw_D[bottom].get_y()}")

    # obwód górny ułożony współzegarowo
    obw_G = []
    top = 0
    obw_G.append(w[-1])
    for i in range(rozmiar - 2, 0, -1):
        if w[i].get_x() >= obw_G[-1].get_x():
            obw_G.append(w[i])
        if w[i].get_x() < obw_G[0].get_x():
            obw_G.insert(0, w[i])
            top += 1

    print()
    for point in obw_G:
        print(f"{point.get_x()}  {point.get_y()}")
    print(f"top  {top}  {obw_G[top].get_x()}  {obw_G[top].get_y()}")

    # sprawdzanie wklęsłości w górnym obwodzie
    while True:
        spr1 = False
        i = 0
        while i <= len(obw_G) - 3:
            a = (obw_G[i+2].get_y() - obw_G[i].get_y()) / (obw_G[i+2].get_x() - obw_G[i].get_x())
            b = obw_G[i].get_y() - obw_G[i].get_x() * a
            if obw_G[i + 1].get_y() < a * obw_G[i + 1].get_x() + b:
                del obw_G[i + 1]
                spr1 = True
            else:
                i += 1
        if not spr1:
            break

    # sprawdzanie wklęsłości w dolnym obwodzie
    while True:
        spr1 = False
        i = 0
        while i <= len(obw_D) - 3:
            a = (obw_D[i + 2].get_y() - obw_D[i].get_y()) / (obw_D[i + 2].get_x() - obw_D[i].get_x())
            b = obw_D[i].get_y() - obw_D[i].get_x() * a
            if obw_D[i + 1].get_y() > a * obw_D[i + 1].get_x() + b:
                del obw_D[i + 1]
                spr1 = True
            else:
                i += 1
        if not spr1:
            break

    print()
    for point in obw_G:
        print(f"{point.get_x()}  {point.get_y()}")
    print()
    for point in obw_D:
        print(f"{point.get_x()}  {point.get_y()}")

    # zapisywanie wyników do plików
    with open("wynik.txt", "w") as wynik:
        wynik.write("x\ty\n")
        for point in obw_G:
            wynik.write(f"{point.get_x()}\t{point.get_y()}\n")
        for point in obw_D[1:]:
            wynik.write(f"{point.get_x()}\t{point.get_y()}\n")

    end = time.time()
    elapsed = end - begin
    print(f"\nczas: {elapsed}")

if __name__ == "__main__":
    main()


您有无限多的硬币，硬币的面值为1,5,11。
给定一个数额w，问您最少用多少枚硬币可以凑出w.

f(w) = min(f(w-1), f(w-5),f(w-11));
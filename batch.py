'''py
 ' @Author: i-curve
 ' @Date: 2023-11-24 16:25:06
 ' @Last Modified by: i-curve
 ' @Name: 
'''
l = ["v1"]

with open("data.h", "w") as f:
    for i in range(0, 64):
        f.write(f"        COPYPP_SETFIELD{64-i},  \\\n")
        pass
    for i in range(2, 65):
        l.append(f'v{i}')
        # print(", ".join(l))
        # f.write(#define COPYPP_SETFIELD1(v1) _COPYPP_EXPANG_SETFIELD(v1)
        #     f"#define COPYPP_PASTE{i}({', '.join(l)}) destination.v1 = source.v1; COPYPP_PASTE{i-1}({', '.join(l[1:])})\n")
        f.write(
            f"#define COPYPP_SETFIELD{i}({', '.join(l)}) _COPYPP_EXPANG_SETFIELD(v1) COPYPP_SETFIELD{i-1}({', '.join(l[1:])})\n")
# print(f"#define COPYPP_PASTE5(v1, v2, v3, v4, v5) destination.v1 = source.v1; COPYPP_PASTE3(v2, v3, v4, v5)")

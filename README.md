# Graph Theory - Chương Trình Đồ Thị C++

Chương trình C++ thực hiện các thao tác cơ bản và nâng cao trên đồ thị, hỗ trợ nhiều cách biểu diễn đồ thị.

## Tính năng chính

### 1. Thao tác cơ bản

- Đọc/Ghi 3 dạng biểu diễn: **Ma trận kề (MTK)**, **Danh sách cạnh (DSC)**, **Danh sách kề (DSK)**
- In đồ thị ra màn hình
- Kiểm tra đồ thị **vô hướng** hay **có hướng**
- Tính **bậc** của các đỉnh và tổng bậc

### 2. Kiểm tra tính chất đồ thị

- Đồ thị đầy đủ (Complete Graph)
- Đồ thị vòng (Cycle Graph)
- Đồ thị hai phía (Bipartite Graph)

### 3. Duyệt đồ thị

- Duyệt **DFS** và **BFS** từ một đỉnh
- Tìm các **thành phần liên thông**

### 4. Thuật toán nâng cao

- Cây khung nhỏ nhất:
  - **Kruskal**
  - **Prim**
- Đường đi ngắn nhất: **Dijkstra**
- Chu trình / Đường đi **Euler**

## Cấu trúc thư mục

```
graph_theory/
├── main/
│   ├── main.cpp
│   ├── graph.h
│   ├── graph.cpp
│   ├── node.cpp
│   └── app.exe
├── io/
│   ├── input.txt
│   ├── output_matrix.txt
│   ├── output_edge.txt
│   └── output_adj.txt
└── README.md
```

## Hướng dẫn Compile & Chạy (Chi tiết)

### Trên Windows

**Cách 1: Sử dụng MinGW (Khuyến nghị)**

1. Đảm bảo đã cài MinGW-w64 và thêm vào PATH.
2. Mở **Command Prompt** hoặc **PowerShell**, di chuyển vào thư mục:

```bash
cd path\to\graph_theory\main
```

3. Compile chương trình:

```bash
g++ -std=c++11 main.cpp graph.cpp -o app.exe
```

4. Chạy chương trình:

```bash
app.exe
```

**Cách 2: Compile với Warning và Optimization**

```bash
g++ -std=c++11 -Wall -Wextra -O2 main.cpp graph.cpp -o app.exe
```

### Trên Linux / macOS

```bash
cd main
g++ -std=c++11 main.cpp graph.cpp -o app
./app
```

## Cách sử dụng

1. Compile như hướng dẫn trên
2. Chạy file `app.exe` (Windows) hoặc `./app` (Linux/macOS)
3. Sử dụng menu để chọn chức năng (Nhập `0` để thoát)

## Input mẫu

Sử dụng file `io/input.txt` chứa ma trận kề mẫu (đồ thị 6 đỉnh).

## Công nghệ

- Ngôn ngữ: **C++11**
- Thư viện: `vector`, `queue`, `stack`, `algorithm`, `fstream`

## Tác giả

**HoangQuyCoder**

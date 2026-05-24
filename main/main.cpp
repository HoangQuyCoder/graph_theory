#include "graph.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    int default_n = 5;
    Graph* g = new Graph(default_n);
    int choice;
    string path;
    int v;
    int s = 1, t = 1;

    do {
        cout << "================== CHUONG TRINH DO THI ==================\n";
        cout << "1. Doc ma tran ke tu file\n";
        cout << "2. Doc danh sach canh tu file\n";
        cout << "3. Doc danh sach ke tu file\n";
        cout << "4. In ma tran ke ra man hinh\n";
        cout << "5. In danh sach canh ra man hinh\n";
        cout << "6. In danh sach ke ra man hinh\n";
        cout << "7. Ghi ma tran ke vao file\n";
        cout << "8. Ghi danh sach canh vao file\n";
        cout << "9. Ghi danh sach ke vao file\n";
        cout << "10. Kiem tra do thi vo huong hay co huong\n";
        cout << "11. Tinh va hien thi bac cua do thi\n";
        cout << "12. Kiem tra do thi day du\n";
        cout << "13. Kiem tra do thi vong\n";
        cout << "14. Kiem tra do thi hai phia\n";
        cout << "15. Duyet DFS tu mot dinh\n";
        cout << "16. Duyet BFS tu mot dinh\n";
        cout << "17. Liet ke cac thanh phan lien thong\n";
        cout << "18. Doc danh sach canh co trong so tu file\n";
        cout << "19. Tim cay khung nho nhat bang Kruskal\n";
        cout << "20. Tim cay khung nho nhat bang Prim\n";
        cout << "21. Tim duong di ngan nhat bang Dijkstra\n";
        cout << "22. Tim chu trinh/duong di Euler\n";
        cout << "0. Thoat chuong trinh\n";
        cout << "=========================================================\n";
        cout << "Nhap lua chon: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Nhap duong dan file ma tran ke: ";
                cin >> path;
                g->readMTK(path);
                cout << "Doc file thanh cong!\n\n";
                break;
            case 2:
                cout << "Nhap duong dan file danh sach canh: ";
                cin >> path;
                g->readDSC(path);
                cout << "Doc file thanh cong!\n\n";
                break;
            case 3:
                cout << "Nhap duong dan file danh sach ke: ";
                cin >> path;
                g->readDSK(path);
                cout << "Doc file thanh cong!\n\n";
                break;
            case 4:
                g->printMTK();
                cout << "\n";
                break;
            case 5:
                g->printDSC();
                cout << "\n";
                break;
            case 6:
                g->printDSK();
                cout << "\n";
                break;
            case 7:
                cout << "Nhap duong dan file de ghi ma tran ke: ";
                cin >> path;
                g->writeMTK(path);
                cout << "Ghi file thanh cong!\n\n";
                break;
            case 8:
                cout << "Nhap duong dan file de ghi danh sach canh: ";
                cin >> path;
                g->writeDSC(path);
                cout << "Ghi file thanh cong!\n\n";
                break;
            case 9:
                cout << "Nhap duong dan file de ghi danh sach ke: ";
                cin >> path;
                g->writeDSK(path);
                cout << "Ghi file thanh cong!\n\n";
                break;
            case 10:
                if (g->unDirected()) {
                    cout << "Do thi vo huong (Undirected graph)\n\n";
                } else {
                    cout << "Do thi co huong (Directed graph)\n\n";
                }
                break;
            case 11:
                if (g->unDirected()) {
                    cout << "Tong bac cua do thi: " << g->sumDeg() << "\n";
                    cout << "Nhap dinh muon xem bac: ";
                    cin >> v;
                    cout << "Bac cua dinh " << v << ": " << g->deg(v) << "\n\n";
                } else {
                    cout << "Tong ban bac ra: " << g->sumDegOut() << "\n";
                    cout << "Tong ban bac vao: " << g->sumDegIn() << "\n";
                    cout << "Nhap dinh muon xem bac: ";
                    cin >> v;
                    cout << "Ban bac ra cua dinh " << v << ": " << g->degOut(v) << "\n";
                    cout << "Ban bac vao cua dinh " << v << ": " << g->degIn(v) << "\n\n";
                }
                break;
            case 12:
                if (g->isGraphFull()) {
                    cout << "Do thi day du (Complete graph)\n\n";
                } else {
                    cout << "Do thi KHONG phai do thi day du\n\n";
                }
                break;
            case 13:
                if (g->isGraphCircle()) {
                    cout << "Do thi vong (Cycle graph)\n\n";
                } else {
                    cout << "Do thi KHONG phai do thi vong\n\n";
                }
                break;
            case 14:
                if (g->isBipartite()) {
                    cout << "Do thi hai phia (Bipartite graph)\n\n";
                } else {
                    cout << "Do thi KHONG phai do thi hai phia\n\n";
                }
                break;
            case 15:
                cout << "Nhap dinh bat dau duyet DFS: ";
                cin >> v;
                cout << "Ket qua DFS: ";
                g->DFS(v);
                cout << "\n\n";
                break;
            case 16:
                cout << "Nhap dinh bat dau duyet BFS: ";
                cin >> v;
                cout << "Ket qua BFS: ";
                g->BFS(v);
                cout << "\n\n";
                break;
            case 17: {
                int tplt = 0;
                g->connectedComponent(tplt);
                cout << "So thanh phan lien thong: " << tplt << "\n\n";
                break;
            }
            case 18: {
                cout << "Nhap duong dan file danh sach canh co trong so: ";
                cin >> path;
                char isUndirChoice;
                cout << "Do thi vo huong? (y/n): ";
                cin >> isUndirChoice;
                bool isUndir = (isUndirChoice == 'y' || isUndirChoice == 'Y');
                g->readDSC_weighted(path, isUndir, s, t);
                cout << "Doc file thanh cong! (Dinh bat dau s = " << s << ", Dinh ket thuc t = " << t << ")\n\n";
                break;
            }
            case 19:
                g->Kruskal();
                cout << "\n";
                break;
            case 20:
                cout << "Nhap dinh bat dau cho Prim: ";
                cin >> v;
                g->Prim(v);
                cout << "\n";
                break;
            case 21: {
                int startNode, endNode;
                cout << "Nhap dinh nguon (Mac dinh tu file s = " << s << "): ";
                cin >> startNode;
                cout << "Nhap dinh dich (Mac dinh tu file t = " << t << "): ";
                cin >> endNode;
                g->Dijkstra(startNode, endNode);
                cout << "\n";
                break;
            }
            case 22:
                cout << "Nhap dinh bat dau Euler: ";
                cin >> v;
                g->Euler(v);
                cout << "\n";
                break;
            case 0:
                cout << "Tam biet!\n";
                break;
            default:
                cout << "Lua chon khong hop le, vui long nhap lai!\n\n";
        }
    } while (choice != 0);

    delete g;
    return 0;
}
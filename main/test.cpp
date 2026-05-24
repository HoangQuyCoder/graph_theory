#include "graph.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
    Graph *g = new Graph(6);

    cout << "--- Doc ma tran ke tu input.txt ---" << endl;
    g->readMTK("../io/input.txt");
    g->printMTK();
    cout << endl;
    
    g->printDSC();
    cout << endl;
    
    g->printDSK();
    cout << endl;

    cout << "--- Ghi do thi ra cac file khac nhau ---" << endl;
    g->writeMTK("../io/output_matrix.txt");
    g->writeDSC("../io/output_edge.txt");
    g->writeDSK("../io/output_adj.txt");
    cout << "Da ghi: output_matrix.txt, output_edge.txt, output_adj.txt" << endl << endl;

    int tongBac;
    int bacDinh1;
    int tongBanBacRa;
    int tongBanBacVao;
    int x1;
    int x2;

    cout << "--- Kiem tra thuoc tinh do thi ---" << endl;
    if (g->unDirected())
    {
        cout << "Do thi vo huong" << endl;
        tongBac = g->sumDeg();
        bacDinh1 = g->deg(1);
        cout << "Tong so bac cua do thi: " << tongBac << endl;
        cout << "Bac cua dinh 1: " << bacDinh1 << endl;
    }
    else
    {
        cout << "Do thi co huong" << endl;
        tongBanBacRa = g->sumDegOut();
        tongBanBacVao = g->sumDegIn();
        x1 = g->degOut(2);
        x2 = g->degIn(2);
        cout << "Tong ban bac ra: " << tongBanBacRa << endl;
        cout << "Tong ban bac vao: " << tongBanBacVao << endl;
        cout << "Ban bac ra cua dinh 2: " << x1 << endl;
        cout << "Ban bac vao cua dinh 2: " << x2 << endl;
    }

    if (g->isGraphFull())
        cout << "Do thi day du: CO" << endl;
    else
        cout << "Do thi day du: KHONG" << endl;

    if (g->isGraphCircle())
        cout << "Do thi vong: CO" << endl;
    else
        cout << "Do thi vong: KHONG" << endl;

    if (g->isBipartite())
        cout << "Do thi hai phia: CO" << endl;
    else
        cout << "Do thi hai phia: KHONG" << endl;

    cout << endl << "--- Duyet do thi ---" << endl;
    cout << "DFS tu dinh 1: ";
    g->DFS(1);
    cout << endl;
    
    cout << "BFS tu dinh 1: ";
    g->BFS(1);
    cout << endl << endl;

    cout << "--- Cac thanh phan lien thong ---" << endl;
    int tplt = 0;
    g->connectedComponent(tplt);
    cout << "So thanh phan lien thong: " << tplt << endl;

    if (tplt == 1)
        cout << "Kiet luan: Do thi lien thong" << endl;
    else
        cout << "Ket luan: Do thi khong lien thong" << endl;
        
    delete g;
    return 0;
}

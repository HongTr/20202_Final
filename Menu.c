#include "Graphlib.h"

int main(){
    Graph graph = createGraph();
    FILE *vocab, *dis;
    vocab = fopen("vocab.txt", "r");
    dis = fopen("graph.txt", "r");
    if (vocab == NULL || dis == NULL){
        printf("Error\n");
        exit(1);
    }
    int choice;
    int flag = 0;
    do{
        printf("=====================================\n");
        printf("1. Doc files\n");
        printf("2. Kiem tra lien ke\n");
        printf("3. Tim duong ngan nhat\n");
        printf("4. Doc van ban\n");
        printf("5. Thoat\n");
        printf("=====================================\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);
        if (choice <= 0 || choice >= 6) printf("Nhap khong hop le!\n");
        else if (choice >=1 && choice <=5){
            switch(choice){
                case 1:
                    if (!flag){
                        flag = 1;
                        //Add Vertices
                        int so_tu;
                        fscanf(vocab, "%d\n", &so_tu);
                        int node;
                        char noidung[20];
                        for (int i = 0; i < so_tu; i++){
                            fscanf(vocab, "%s %d\n", &noidung, &node);
                            addVertex(graph, node, strdup(noidung));
                        }

                        //Add Edges
                        int so_canh;
                        fscanf(dis, "%d\n", &so_canh);
                        double weight;
                        int v1, v2;
                        for (int i = 0; i < so_canh; i++){
                            fscanf(dis, "%lf %d %d\n", &weight, &v1, &v2);
                            addEdge1(graph, v1, v2, weight);
                        }
                        //Print_Graph_Map(graph);
                        //Print_Graph_Vertex(graph);
                        printf("Ban da doc xong file\n");
                    }
                    else printf("Ban da doc file\n");
                    break;
                case 2:
                    if (flag){
                        char w1[20], w2[20];
                        goal1:
                        printf("Nhap tu: ");
                        scanf("%s %s", &w1, &w2);
                        int v1 = return_ID(graph, w1);
                        int v2 = return_ID(graph, w2);
                        //printf("%d %d", v1, v2);
                        if (getVertex(graph, v1) == NULL || getVertex(graph, v2) == NULL){
                            printf("Khong co tu!\n");
                            goto goal1;
                        }
                        if (v1 == v2){
                            printf("Nhap khong hop le!\n");
                            goto goal1;
                        }
                        if (hasEdge(graph, v1, v2)) printf("%.5lf\n", getEdgeValue(graph, v1, v2));
                        else printf("Not adjacent.\n");
                    }
                    else printf("Ban chua doc file\n");
                    break;
                case 3:
                    if (flag){
                        char w1[20], w2[20];
                        goal2:
                        printf("Nhap tu: ");
                        scanf("%s %s", &w1, &w2);
                        int v1 = return_ID(graph, w1);
                        int v2 = return_ID(graph, w2);
                        //printf("%d %d", v1, v2);
                        if (getVertex(graph, v1) == NULL || getVertex(graph, v2) == NULL){
                            printf("Khong co tu!\n");
                            goto goal2;
                        }
                        if (v1 == v2){
                            printf("Nhap khong hop le!\n");
                            goto goal2;
                        }
                        int length, path[1000];
                        double distance = dijkstra(graph, v1, v2, path, &length);
                        if (distance == INFINITIVE_VALUE) printf("No path\n");
                        else{
                            printf("Shortest Path: %.5lf\n", distance);
                        }
                    }
                    else printf("Ban chua doc file\n");
                    break;
                case 4:
                    if (flag){
                        IS f1 = new_inputstruct("input.txt");
                        if (f1 == NULL){
                            printf("Error!\n");
                            exit(1);
                        }
                        get_line(f1);
                        int so_cau = atoi(f1->fields[0]);
                        Info info[so_cau];
                        for (int i = 0; i < so_cau; i++){
                            info[i].count = 0;
                            info[i].score = 0;
                        }
                        int so_tu;
                        for (int i = 0; i < so_cau; i++){
                            get_line(f1);
                            so_tu = atoi(f1->fields[0]);
                            for (int j = 1; j < so_tu; j++){
                                if (hasEdge(graph, return_ID(graph, f1->fields[j]), return_ID(graph, f1->fields[j+1]))){
                                    info[i].count += 1;
                                    info[i].score += getEdgeValue(graph, return_ID(graph, f1->fields[j]), return_ID(graph, f1->fields[j+1]));
                                    info[i].line = i+1;
                                    info[i].tong_diem = info[i].score/info[i].count;
                                }
                            }
                        }
                        // Array bao gom cac struct chua score va count tung cau
                        double diem1, diem2;
                        Info temp;
                        for (int i = 0; i < so_cau - 1; i++){
                            for (int j = i+1; j < so_cau; j++){
                                if (info[i].tong_diem > info[j].tong_diem){
                                    temp = info[i];
                                    info[i] = info[j];
                                    info[j] = temp;
                                }
                            }
                        }
                        jettison_inputstruct(f1);
                        //Array info da duoc sort theo tong_diem;
                        int n;
                        goal3:
                        printf("Nhap n (0<n<10): "); scanf("%d", &n);
                        if (n <= 0 || n >= 10){
                            printf("Nhap khong hop le!\n");
                            goto goal3;
                        }
                        if (n > so_cau){
                            printf("Nhap khong hop le!\n");
                            goto goal3;
                        }
                        /*for (int i = 0; i < so_cau; i++){
                            printf("Cau %d\n", info[i].line);
                        }*/
                        IS f2 = new_inputstruct("input.txt");
                        if (f2 == NULL){
                            printf("Error!\n");
                            exit(1);
                        }
                        int so_cau_temp;
                        
                        get_line(f2);
                        so_cau_temp = atoi(f2->fields[0]);
                        int so_tu_temp;
                        
                        Noi_dung noi_dung[so_cau_temp]; // Bao gom so line va noi dung line do
                        
                        for (int i = 0; i < so_cau_temp; i++){
                            get_line(f2);
                            so_tu_temp = atoi(f2->fields[0]);
                            if (so_tu_temp == 1) strcpy(noi_dung[i].cau, f2->fields[1]);
                            else{
                                strcpy(noi_dung[i].cau, f2->fields[1]);
                                for (int j = 2; j <= so_tu_temp; j++){
                                    noi_dung[i].line = i+1;
                                    strcat(noi_dung[i].cau, " ");
                                    strcat(noi_dung[i].cau, f2->fields[j]);
                                }
                            }
                        }

                        // IN CAC CAU
                        for (int i = 0; i < n; i++){
                            for (int j = 0; j < so_cau_temp; j++){
                                if (info[i].line == noi_dung[j].line){
                                    printf("%s\n", noi_dung[j].cau);
                                    break;
                                }
                            }
                        }
                    }
                    else printf("Ban chua doc file\n");
                    break;
                case 5: printf("Ban da thoat chuong trinh!\n");
                    break;
            }
        }
    }while(choice != 5);
    fclose(vocab);
    fclose(dis);
    return 1;
}
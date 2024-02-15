#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;
string filename = "Data.txt"; //Tên của file dữ liệu
ifstream Input(filename); //Nhập dữ liệu vào 

//Xây dựng cấu trúc dữ liệu
struct Person{
//Chứa các dữ liệu thông tin sinh viên 
   string name, age, score;
};

//Truyền vào Reference để có thể thay đổi được dữ liệu
int load_person(string filename, vector<Person>& person_list){
    string line;
    int count =0;
    
    while(getline(Input,line)){
        int f = line.find(";"); //Thực hiện tìm kiếm vị trí của kí tự phân cách

        //Vòng lặp diễn ra khi tìm thấy kí tự phân cách
        while(f!= string::npos){ 
           Person new_person; //Dùng làm biến trung gian để push_back vào cuối vector
           
           new_person.name = line.substr(0,f); //Thêm name
           line = line.substr(f+1); //Thực hiện cắt name khỏi line


           f = line.find(";"); //Thực hiện gán lại để tìm tiếp
            new_person.age = line.substr(0,f);
            line = line.substr(f+1); //Thực hiện cắt tuổi khỏi line

            new_person.score = line; //Thực hiện gán tuổi

            person_list.push_back(new_person); //Thêm vào phía sau vector

            count++; //Tăng số lượng thành viên lên 1

            f = line.find(";"); //Thực hiện tìm không thấy sẽ thoát khỏi vòng lặp

        }

    }

    return count;
};

//Thực hiện việc update lại dữ liệu từ vector vào bên trong file txt
void update_person(string filename, vector<Person>& person_list, int& count){
    ofstream Output(filename,ofstream::out); //Thực hiện việc thêm dữ liệu vào đằng sau file txt
    for(int i = 0; i <= count - 2; i++){
        Output << person_list[i].name << ";" << person_list[i].age << ";" << person_list[i].score << endl; 
    }
    Output << person_list[count-1].name<< ";" << person_list[count-1].age<< ";" << person_list[count-1].score;
}

//Thực hiện tìm kiếm kí tự trong tên sinh viên
void find_char_person(vector<Person> person_list, string find_char){
    int count = 0;
    vector<Person> copy_find_char_person; //Lưu trữ kí tự cần tìm

    //Vòng for thực hiện push_back các vector có kí tự find_char vào cuối copy_find_char_person
    for(int i = 0; i < person_list.size(); i++){ 
        int j = person_list[i].name.find(find_char); //Thực hiện tìm kiếm 
        if(j != string::npos){ //Nếu như tìm thấy sẽ push_back vào phía sau copy_find_char_person
            copy_find_char_person.push_back(person_list[i]); //Push_back vào cuối
            count++;
        }

        else continue; //Nếu không tìm thấy sẽ switch qua vòng tiếp
    }

    cout << "\t\t+--------+------------------------------+--------+--------+\n";
    cout << "\t\t|  STT   |  Ho Ten                      |  Tuoi  |  Diem  |\n";
    cout << "\t\t+--------+------------------------------+--------+--------+\n";
    for (int i = 0; i < count; i++) {
        cout << "\t\t|  " << left << setw(6) << i + 1
             << "|  " << left << setw(28) << copy_find_char_person[i].name
             << "|  " << left << setw(6) << copy_find_char_person[i].age
             << "|  " << left << setw(6) << copy_find_char_person[i].score
             << "|" << endl;
    }
    cout << "\t\t+--------+------------------------------+--------+--------+\n";
}

//Thực hiện việc sắp xếp lại tên theo bản chữ cái
void sort_name(vector<Person> person_list, int count){
    vector<Person> person_sort_name(count);

    for(int i = 0; i < count; i++){ //Thực hiện việc tách tên khỏi họ và tên đệm cho person_list
        int j = person_list[i].name.find(" ");
        
        while(j != string::npos){
            if(person_sort_name[i].name == ""){
                person_sort_name[i].name = person_list[i].name.substr(0,j);
                person_sort_name[i].age = person_list[i].age;
                person_sort_name[i].score = person_list[i].score;
            }
            else{
                person_sort_name[i].name += (" " + person_list[i].name.substr(0,j));
                person_sort_name[i].age = person_list[i].age;
                person_sort_name[i].score = person_list[i].score;               
            }
            person_list[i].name = person_list[i].name.substr(j+1);
            j = person_list[i].name.find(" "); 
        }
    }

//Selection sort cho việc sắp xếp lại tên theo thú tự
    for(int i = 0 ; i < count ; i++){
        int min_index = i;
        for(int j = i + 1; j < count; j++){
            if(person_list[j].name < person_list[min_index].name){
                min_index = j;
            }
        }
    
        swap(person_list[i], person_list[min_index]);
        swap(person_sort_name[i], person_sort_name[min_index]);
    }

    //Thực hiện việc ghép họ và tên đệm vào tên cũng như cập nhật lại tuổi
    for(int i = 0; i < count; i++){
    if(person_sort_name[i].name == ""){ //Nếu như xâu rỗng
        person_sort_name[i].name = person_list[i].name;
        person_sort_name[i].age = person_list[i].age;
        person_sort_name[i].score = person_list[i].score;
    }

    else{//Nếu như xâu đã có kí tự
        person_sort_name[i].name += (" " + person_list[i].name);
        person_sort_name[i].age = person_list[i].age;
        person_sort_name[i].score = person_list[i].score;
    }
    }

    cout << "\t\t+--------+------------------------------+--------+--------+\n";
    cout << "\t\t|  STT   |  Ho Ten                      |  Tuoi  |  Diem  |\n";
    cout << "\t\t+--------+------------------------------+--------+--------+\n";
    for (int i = 0; i < count; i++) {
        cout << "\t\t|  " << left << setw(6) << i + 1
             << "|  " << left << setw(28) << person_sort_name[i].name
             << "|  " << left << setw(6) << person_sort_name[i].age
             << "|  " << left << setw(6) << person_sort_name[i].score
             << "|" << endl;
    }
    cout << "\t\t+--------+------------------------------+--------+--------+\n";   
}

//Thực hiện việc sắp xếp lại tuổi theo thứ tự tăng dần
void sort_age(vector<Person> person_list, int count){
    for(int i = 0 ; i < count ; i++){ //Selection sort sắp xếp lại tuổi
        int min_index = i;
        for(int j = i + 1; j < count; j++){
            if(person_list[j].age < person_list[min_index].age){
                min_index = j;
            }
        }
    
        swap(person_list[i], person_list[min_index]);
    }

    cout << "\t\t+--------+------------------------------+--------+--------+\n";
    cout << "\t\t|  STT   |  Ho Ten                      |  Tuoi  |  Diem  |\n";
    cout << "\t\t+--------+------------------------------+--------+--------+\n";
    for (int i = 0; i < count; i++) {
        cout << "\t\t|  " << left << setw(6) << i + 1
             << "|  " << left << setw(28) << person_list[i].name
             << "|  " << left << setw(6) << person_list[i].age
             << "|  " << left << setw(6) << person_list[i].score
             << "|" << endl;
    }
    cout << "\t\t+--------+------------------------------+--------+--------+\n"; 


}

//Thực hiện việc sắp xếp lại điểm theo thứ tự tăng dần
void sort_score(vector<Person> person_list, int count){
    for(int i = 0 ; i < count ; i++){ //Selection sort sắp xếp lại tuổi
        int min_index = i;
        for(int j = i + 1; j < count; j++){
            if(stof(person_list[j].score) < stof(person_list[min_index].score)){
                min_index = j;
            }
        }
    
        swap(person_list[i], person_list[min_index]);
    }

    cout << "\t\t+--------+------------------------------+--------+--------+\n";
    cout << "\t\t|  STT   |  Ho Ten                      |  Tuoi  |  Diem  |\n";
    cout << "\t\t+--------+------------------------------+--------+--------+\n";
    for (int i = 0; i < count; i++) {
        cout << "\t\t|  " << left << setw(6) << i + 1
             << "|  " << left << setw(28) << person_list[i].name
             << "|  " << left << setw(6) << person_list[i].age
             << "|  " << left << setw(6) << person_list[i].score
             << "|" << endl;
    }
    cout << "\t\t+--------+------------------------------+--------+--------+\n";

}

//Thực hiện tính điểm trung bình cả lớp
float arithmetic_mean(vector<Person> person_list, int count){
    float plus = 0;
    for(int i = 0; i < count; i++){
        plus += stof(person_list[i].score);
    }
    return (plus/count);
}

//Thực hiện tính tỉ lệ sinh viên giỏi
float good(vector<Person> person_list, int count){
    float plus = 0;
    for(int i = 0; i < count; i++){
        if(stof(person_list[i].score) >= 8 ){
            plus++;
        }
    }

    float r = ((plus/count) * 100);
    return r;
}

//Thực hiện tính tỉ lệ sinh viên khá
float quiet(vector<Person> person_list, int count){
    float plus = 0;
    for(int i = 0; i < count; i++){
        if(stof(person_list[i].score) < 8 && stof(person_list[i].score) >= 6.5){
            plus++;
        }
    }

    float r = ((plus/count) * 100);
    return r;
}

//Tìm sinh viên có giá điểm cao nhất
void find_person_max_score(vector<Person> person_list, int count){
        for(int i = 0 ; i < count ; i++){ //Selection sort sắp xếp lại tuổi
        int min_index = i;
        for(int j = i + 1; j < count; j++){
            if(stof(person_list[j].score) < stof(person_list[min_index].score)){
                min_index = j;
            }
        }
    
        swap(person_list[i], person_list[min_index]);
    }


    for(int i = 0; i < count;i++){
        if(stof(person_list[i].score) == stof(person_list[count-1].score)){
            cout << person_list[i].name << " | " ;
        }
    }
    cout << endl;
}

int main(){
    string press; //Nhấn vào menu


    //Vector lưu trữ các sinh viên
    vector<Person> person_list; 
    int count = load_person(filename,person_list); //Vị trí của sinh viên n bằng count - 1

    
    
    while(true){
    cout << "Danh sach thao tac: \n" 
    << "1 - In danh sach sinh vien\n"
    << "2 - Them\n"
    << "3 - Sua\n"
    << "4 - Xoa\n"
    << "5 - Tim kiem\n"
    << "6 - Sap xep\n"
    << "7 - Thong ke\n"
    << "8 - Sao luu\n"
    << "9 - Thoat\n"
    << "Nhap lenh: "; 
    cin >> press;


    if(press == "1") {
    cout << count << endl;
    cout << "[1] In danh sach sinh vien:\n";
    cout << "\t\t+--------+------------------------------+--------+--------+\n";
    cout << "\t\t|  STT   |  Ho Ten                      |  Tuoi  |  Diem  |\n";
    cout << "\t\t+--------+------------------------------+--------+--------+\n";
    for (int i = 0; i < count; i++) {
        cout << "\t\t|  " << left << setw(6) << i + 1
             << "|  " << left << setw(28) << person_list[i].name
             << "|  " << left << setw(6) << person_list[i].age
             << "|  " << left << setw(6) << person_list[i].score
             << "|" << endl;
    }
    cout << "\t\t+--------+------------------------------+--------+--------+\n";
}  
    else if(press == "2") {
        ofstream Output(filename,ios::app); //Thực hiện việc thêm dữ liệu vào đằng sau file txt
        Person new_person; //Biến trung gian để import vào file txt
        cout << "[2] Them sinh vien\n"; 
        cin.ignore(); //Xóa kí tự thừa Enter
        cout << "\t\t (?) Nhap ten: " ; getline(cin,new_person.name);
        cout << "\t\t (?) Nhap tuoi: "; getline(cin,new_person.age);
        cout << "\t\t (?) Nhap diem: "; getline(cin,new_person.score);
        person_list.push_back(new_person); //Push_back vào sau vector
        //Thực hiện import vào file
        Output << endl <<person_list[count].name << ";" << person_list[count].age << ";" << person_list[count].score;     
        count++; //Tăng thêm 1 người 
    }    
    else if(press == "3") {
        int change_count; //Nhập số thứ tự sinh viên cần sửa. Vị trí = change_count - 1
        int change_element; //Muốn sửa thành phần gì trong sinh viên
        cout << "[3] Sua thong tin sinh vien\n"
             << "\t\t (?) Nhap STT cua sinh vien can sua: "; cin >> change_count;
        cout << "\t\t (?) Ban muon sua gi: \n"
             << "\t\t 1 - Ten\n"
             << "\t\t 2 - Tuoi\n"
             << "\t\t 3 - Diem\n"
             << "\t\t (?) Chon: "; cin >> change_element;
                cin.ignore();
        //Thực hiện việc thay đổi phần tử
        
            if(change_element == 1){
                cout << "\t\t (?) Nhap ten: "; getline(cin,person_list[change_count - 1].name); //Thực hiện cập nhật lại tên sinh viên
                update_person(filename,person_list,count); //Update lại file bằng các phần tử có trong vector
            }

            if(change_element == 2){
                cout << "\t\t (?) Nhap tuoi: "; getline(cin,person_list[change_count - 1].age); //Thực hiện cập nhật lại tuổi sinh viên
                update_person(filename,person_list,count); //Update lại file bằng các phần tử có trong vector
            }

            if(change_element == 3){
                cout << "\t\t (?) Nhap diem: "; getline(cin,person_list[change_count - 1].score); //Thực hiện cập nhật lại điểm sinh viên
                update_person(filename,person_list,count); //Update lại file bằng các phần tử có trong vector
            }
        

    }
    else if(press == "4") {
        int change_count; //Nhập số thứ tự sinh viên cần sửa. Vị trí vector = change_count - 1
        cout << "[4] Xoa sinh vien\n"
             << "\t\t(?) Nhap STT: "; cin >> change_count;

        if(change_count - 1 >= 0 && change_count - 1 < count){
            person_list.erase(person_list.begin() + (change_count -1)); //Thực hiện việc xóa sinh viên
            count--; //Giảm xóa sinh viên đi 1 đơn vị đối với biến đến
            update_person(filename,person_list,count); 
            cout << "\t\t(!) Da xoa sinh vien có STT la: " << change_count << endl; //Thông báo đã xóa sinh viên
        }

        //Nếu sai số thứ tự hoặc không có số thứ tự
        else{
            cout << "\t\tSo thu tu khong hop le. Vui long thu lai sau!\n";
        }
    }
    else if(press == "5") {
        cin.ignore(); //Xóa kí tự thừa
        string find_char;
        cout << "[5] Tim kiem\n"
             << "\t\t (?) Nhap ki tu: "; getline(cin,find_char);
        find_char_person(person_list,find_char);
    }
    else if(press == "6") {
        int choose;
        cout << "[6] - Sap xep\n"
             << "\t\t(!) Sap xep the nao: \n"
             << "\t\t(!) 1 - Sap xep theo ten ABC\n"
             << "\t\t(!) 2 - Sap xep theo tuoi tang dan\n"
             << "\t\t(!) 3 - Sap xep theo diem tang dan\n"
             << "\t\t(?) Chon: "; cin >> choose;
         
            if(choose == 1){
                sort_name(person_list, count);
            }

            if(choose == 2){
                sort_age(person_list,count);
            }

            if(choose == 3){
                sort_score(person_list,count);
            }
    }
    else if(press == "7") {
        cout << "[7] Thong ke\n";
        cout << "\t\t (!) Diem trung binh ca lop: "; cout << arithmetic_mean(person_list,count); cout << endl;
        cout << "\t\t (!) Ti le sinh vien gioi: ";   cout << good(person_list,count); cout << "%\n";
        cout << "\t\t (!) Ti le sinh vien kha: ";    cout << quiet(person_list,count); cout << "%\n";
        cout << "\t\t (!) Ti le sinh vien kem: ";    cout << (100 - good(person_list,count) - quiet(person_list,count)); cout << "%\n";
        cout << "\t\t (!) Sinh vien diem cao nhat la: ";  find_person_max_score(person_list, count);
    }
    else if(press == "8") {

    }
    else if(press == "9"){
        exit(0); //Thoát khỏi chương trình
    }
    else cout << "\t Lenh khong hop le!\n";

    cout << "Press any key to continue...";
    cin.ignore();
    getline(cin, press);
    cout << "\033[H\033[J";    
    }
}
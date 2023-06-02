#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct TreeNode {
    int plakaKodu;
    string sehir;
    TreeNode* left;
    TreeNode* right;
};

//ekle fonksiyonu, plaka koduna göre düğümleri uygun şekilde yerleştirir. 

void ekle(TreeNode*& root, int plakaKodu, const string& sehir) {
    if (root == nullptr) {
        root = new TreeNode;
        root->plakaKodu = plakaKodu;
        root->sehir = sehir;
        root->left = nullptr;
        root->right = nullptr;
    }
    else if (plakaKodu < root->plakaKodu) {
        ekle(root->left, plakaKodu, sehir);
    }
    else if (plakaKodu > root->plakaKodu) {
        ekle(root->right, plakaKodu, sehir);
    }
}

//inorder, preorder ve postorder fonksiyonları ağacı sırasıyla gezerek düğüm değerlerini ekrana yazdırır. 

void inorder(TreeNode* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->plakaKodu << " ";
        inorder(root->right);
    }
}

void preorder(TreeNode* root) {
    if (root != nullptr) {
        cout << root->plakaKodu << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(TreeNode* root) {
    if (root != nullptr) {
        postorder(root->left);
        postorder(root->right);
        cout << root->plakaKodu << " ";
    }
}

//derinlik fonksiyonu, bir düğümün derinliğini hesaplar.

int derinlik(TreeNode* root) {
    if (root == nullptr)
        return 0;
    else {
        int solDerinlik = derinlik(root->left);
        int sagDerinlik = derinlik(root->right);
        return max(solDerinlik, sagDerinlik) + 1;
    }
}

//dengeKontrol fonksiyonu, ağacın dengeli olup olmadığını kontrol eder. 

bool dengeKontrol(TreeNode* root) {
    if (root == nullptr)
        return true;

    int solDerinlik = derinlik(root->left);
    int sagDerinlik = derinlik(root->right);

    if (abs(solDerinlik - sagDerinlik) <= 1 && dengeKontrol(root->left) && dengeKontrol(root->right))
        return true;

    return false;
}

//sehirDuzeyFarki fonksiyonu, iki plaka kodunun şehirlerini bulur ve düzey farklarını hesaplar.


int sehirDuzeyFarki(TreeNode* root, int plaka1, int plaka2) {
    if (root == nullptr)
        return -1;

    if (plaka1 < root->plakaKodu && plaka2 < root->plakaKodu)
        return sehirDuzeyFarki(root->left, plaka1, plaka2);

    if (plaka1 > root->plakaKodu && plaka2 > root->plakaKodu)
        return sehirDuzeyFarki(root->right, plaka1, plaka2);

    int plaka1Duzey = derinlik(root) - derinlik(root->left);
    int plaka2Duzey = derinlik(root) - derinlik(root->right);

    return abs(plaka1Duzey - plaka2Duzey);
}

void ağaciYazdir(TreeNode* root, int indent = 0) {
    if (root != nullptr) {
        ağaciYazdir(root->right, indent + 4);
        cout << string(indent, ' ');
        cout << root->plakaKodu << endl;
        ağaciYazdir(root->left, indent + 4);
    }
}

int main() {
    TreeNode* root = nullptr;

    //Bu kodda, sehir_plaka_kodlari.txt dosyasından şehir ve plaka kodlarını okuyarak bir ikili arama ağacı oluşturulmaktadır. 
   
    ifstream dosya("C://Users//user//OneDrive - Manisa Celal Bayar Üniversitesi//Masaüstü//212803041_Beyza_Yoldaş//veriyapıları2//sehir_plaka_kodlari.txt"); 
    if (!dosya.is_open()) {
        cout << "Dosya acma hatasi! Dosya acilamadi!" << endl;
        return 1;
    }

    int plakaKodu;
    string sehir;

    while (dosya >> plakaKodu >> sehir) {
        ekle(root, plakaKodu, sehir);
    }

    dosya.close();

    cout << "Olusturulan agacin goruntusu:" << endl;
    ağaciYazdir(root);

    cout << "Agacin derinligi: " << derinlik(root) << endl;

    if (dengeKontrol(root))
        cout << "Agac dengelidir." << endl;
    else
        cout << "Agac dengeli degildir." << endl;

    //Kod çalıştırıldığında, ağacın görüntüsü, derinliği ve dengeli olup olmadığı ekranda görüntülenecektir.
    //Ardından kullanıcıdan iki plaka kodu istenecek ve bu plaka kodlarına karşılık gelen şehirler ve ağaçtaki düzey farkı ekranda gösterilecektir.
    //Son olarak, ağacın preorder, inorder ve postorder olarak sıralanmış hali ekranda görüntülenecektir.

    int plaka1, plaka2;
    cout << "1. plaka kodunu girin: ";
    cin >> plaka1;
    cout << "2. plaka kodunu girin: ";
    cin >> plaka2;

    cout << "ilk plakanin sehri: ";
    TreeNode* plaka1Node = root;
    while (plaka1Node != nullptr && plaka1Node->plakaKodu != plaka1) {
        if (plaka1 < plaka1Node->plakaKodu)
            plaka1Node = plaka1Node->left;
        else
            plaka1Node = plaka1Node->right;
    }
    if (plaka1Node != nullptr)
        cout << plaka1Node->sehir << endl;
    else
        cout << "Plaka kodu bulunamadi!" << endl;

    cout << "ikinci plakanin sehri: ";
    TreeNode* plaka2Node = root;
    while (plaka2Node != nullptr && plaka2Node->plakaKodu != plaka2) {
        if (plaka2 < plaka2Node->plakaKodu)
            plaka2Node = plaka2Node->left;
        else
            plaka2Node = plaka2Node->right;
    }
    if (plaka2Node != nullptr)
        cout << plaka2Node->sehir << endl;
    else
        cout << "Plaka kodu bulunamadi!" << endl;

    int duzeyFarki = sehirDuzeyFarki(root, plaka1, plaka2);
    if (duzeyFarki != -1)
        cout << "Duzey farki: " << duzeyFarki << endl;
    else
        cout << "Plaka kodu bulunamadi!" << endl;

    

    cout << "Preorder siralamasi: ";
    preorder(root);
    cout << endl;

    cout << "Inorder siralamasi: ";
    inorder(root);
    cout << endl;

    cout << "Postorder siralamasi: ";
    postorder(root);
    cout << endl;

    return 0;
}












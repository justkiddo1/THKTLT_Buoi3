#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#define MAX_SINHVIEN 100
#define MAX_LOP 100 

using namespace std;

typedef struct 
{
	char maso[15];
	float diemTrungBinh;
	char hoTen[30];
}SinhVien;

typedef struct {
	char tenLop[15];
	int siSo;
	SinhVien danhSachSinhVien[MAX_SINHVIEN];
}LopHoc;

int docSVTuFile(const char* tenFile, SinhVien* danhSachSinhVien) {
	FILE* file = fopen(tenFile, "r");
	if (file == NULL) {
		printf("Khong mo duoc file !\n");
		return 0;
	}
	int i = 0;
	while (fscanf(file, "%s %f %s",danhSachSinhVien[i].maso,&danhSachSinhVien[i].diemTrungBinh,danhSachSinhVien[i].hoTen)==3) {
		i++;
	}
	fclose(file);
	return i;
}

int docLopTuFile(const char* tenFile, LopHoc* danhsachLop, int maxLop) {
	FILE* file;
	errno_t err = fopen_s(&file, tenFile, "r");
	if (err != 0 || file==nullptr) {
		printf("Khong mo duoc tep %s. \n",tenFile);
		return 0;
	}
	int  soLop=0;
	while (soLop < maxLop && fscanf(file, "%s %d", danhsachLop[soLop].tenLop, &danhsachLop[soLop].siSo) == 2) {
		char tenFileSV[100];
		sprintf(tenFileSV, "%s.txt", danhsachLop[soLop].tenLop);
		int soSinhVien = docSVTuFile(tenFileSV, danhsachLop[soLop].danhSachSinhVien);
		danhsachLop[soLop].siSo = soSinhVien;
		soLop++;
	}
	fclose(file);
	return soLop;
}

void xuatDanhSachSV(SinhVien* danhsachSinhVien, int soSinhVien) {
	printf("Danh sach sinh vien : \n");
	for (int i = 0; i < soSinhVien; i++) {
		printf("Ma so : %s, Ho ten : %s, Diem TB: %.2f\n", danhsachSinhVien[i].maso, danhsachSinhVien[i].hoTen, danhsachSinhVien[i].diemTrungBinh);
	}
}

void xuatDanhSachLop(LopHoc* danhsachLop, int soLop) {
	printf("Danh sach lop : \n");
	for (int i = 0; i < soLop; i++) {
		printf("Lop : %s , Si so : %d\n", danhsachLop[i].tenLop, danhsachLop[i].siSo);
		xuatDanhSachSV(danhsachLop[i].danhSachSinhVien, danhsachLop[i].siSo);
	}
}



int main() {
	LopHoc danhsachLop[MAX_LOP];
	int soLop;

	soLop = docLopTuFile("dslop.txt", danhsachLop, MAX_LOP);

	xuatDanhSachLop(danhsachLop, soLop);

	return 0;
}
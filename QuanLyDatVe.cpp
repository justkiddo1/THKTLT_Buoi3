#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

struct KhachHang {
	string hoTen;
	string soDienThoai;
	int soVeNL;
	int soVeTE;
	string tenPhim;
	string phongChieu;
	string xuatChieu;
	int tienPhaiTra;
};

vector<KhachHang> docDSKHTuFile(const string& filename) {
	vector<KhachHang> dskh;
	ifstream file(filename);
	string line;

	if (file.is_open()) {
		while (getline(file, line)) {
			stringstream ss(line);
			KhachHang kh;

			getline(ss, kh.hoTen, ';');
			getline(ss, kh.soDienThoai, ';');
			ss >> kh.soVeNL;
			ss.ignore();
			ss >> kh.soVeTE;
			ss.ignore();
			getline(ss, kh.tenPhim, ';');
			getline(ss, kh.phongChieu, ';');
			getline(ss, kh.xuatChieu, ';');
			ss >> kh.tienPhaiTra;

			dskh.push_back(kh);
		}
		file.close();
	}
	return dskh;
}

int TinhTien(const KhachHang& kh) {
	const int GIAVE_NGUOI_LON = 40000;
	const int GIAVE_TRE_EM = 20000;
	return kh.soVeNL * GIAVE_NGUOI_LON + kh.soVeTE * GIAVE_TRE_EM;
}

void xuatDanhSachKH(vector<KhachHang>& dskh) {
	for (auto& kh : dskh) {
		kh.tienPhaiTra = TinhTien(kh);
		cout << "Ho va ten : " << kh.hoTen << endl;
		cout << "So dien thoai : " << kh.soDienThoai << endl;
		cout << "So ve nguoi lon : " << kh.soVeNL << endl;
		cout << "So ve tre em : " << kh.soVeTE << endl;
		cout << "Ten phim : " << kh.tenPhim << endl;
		cout << "Phong chieu : " << kh.phongChieu << endl;
		cout << "Xuat chieu : " << kh.xuatChieu << endl;
		cout << "Tien phai tra : " << kh.tienPhaiTra << endl << endl;
	}
}

float tinh_tong_doanh_thu(const vector<KhachHang>& dskh) {
	float tong_doanh_thu = 0.0;
	for (const auto& kh : dskh) {
		tong_doanh_thu += kh.tienPhaiTra; // Giả sử tien_phai_tra chứa tiền khách hàng phải trả  
	}
	return tong_doanh_thu;
}

void xuat_tong_doanh_thu(const vector<KhachHang>& dskh) {
	float tong_doanh_thu = tinh_tong_doanh_thu(dskh);
	cout << "Tong doanh thu cua rap phim la : " << tong_doanh_thu << endl;
}

void xuat_khach_hang_theo_phong_va_xuat(const vector<KhachHang>& dskh) {
	string phong_chieu;
	string xuat_chieu;

	cout << "Nhap phong chieu: ";
	cin >> phong_chieu;
	cout << "Nhập xuat chieu: ";
	cin >> xuat_chieu;

	cout << "Danh sach khach hang dat ve cho phong chieu " << phong_chieu << " va xuat chieu " << xuat_chieu << ":" << endl;

	for (const auto& kh : dskh) {
		if (kh.phongChieu == phong_chieu && kh.xuatChieu == xuat_chieu) {
			cout << "Ten khach hang: " << kh.hoTen << endl;
			cout << "So dien thoai: " << kh.soDienThoai << endl;
		}
	}
}

void quick_sort(vector<KhachHang>& dskh, int low, int high) {
	if (low < high) {
		float pivot = dskh[high].tienPhaiTra; 
		int i = low - 1;

		for (int j = low; j < high; j++) {
			if (dskh[j].tienPhaiTra < pivot) {
				i++;
				swap(dskh[i], dskh[j]);   
			}
		}
		swap(dskh[i + 1], dskh[high]);  
		int pi = i + 1;

		quick_sort(dskh, low, pi - 1);
		quick_sort(dskh, pi + 1, high);
	}
}

void sap_xep_khach_hang_theo_tien(vector<KhachHang>& dskh) {
	quick_sort(dskh, 0, dskh.size() - 1);
	cout << "Danh sach khach hang sau khi sap xep theo so tien can phai tra :" << endl;
	for (const auto& kh : dskh) {
		cout << "Ten khach hang: " << kh.hoTen << ", Tien phai tra: " << kh.tienPhaiTra << endl;
	}
}

int main() {
	string fileName = "dskh.txt";
	vector<KhachHang> dskh = docDSKHTuFile(fileName);
	xuatDanhSachKH(dskh);
	xuat_tong_doanh_thu(dskh);
	xuat_khach_hang_theo_phong_va_xuat(dskh);
	sap_xep_khach_hang_theo_tien(dskh);
	return 0;
}
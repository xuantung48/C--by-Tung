#include<bits/stdc++.h>
using namespace std;

struct Inven
{
	string Desc,		// Mô tả món hàng
		   Date;		// Ngày được thêm vào kho
	int    Qty;			// Số lượng
	double WhsleCost,	// Chi phí bán buôn
		   RetailCost;	// Chi phí bán lẻ
};


void addRecord(Inven &, fstream &);
void displayRecord(Inven &, fstream &);
void changeRecord(Inven &, fstream &);
long byteNum(int);
void displayError();
bool validDate(string);
void sumCost(Inven &, fstream &);

int main ()
{
	//Inven record;// = {" ", " ", 0, 0.0, 0.0};
	int Input;
    Inven record;
	double Totwhsle  = 0,
		   TotRetail = 0;	
	int TotQty = 0;		
	fstream File("inventory.dat", ios::out | ios::in | ios::binary);
	if (!File)
	{
		cout << "Error opening file.\n";
		return 0;
	}

	cout << "               Menu chương trình hàng tồn kho.\n"
		 << "Chọn một trong các muc sau để thực hiện một nhiệm vụ:\n";
	cout << " 1. Thêm bản ghi Inventorymới vào tệp.\n";
	cout << " 2. Hiển thị bất kỳ bản ghi nào trong tệp.\n";
	cout << " 3. Thay đổi bất kỳ bản ghi nào trong tệp.\n";
	cin  >> Input;

	switch (Input)
	{
		case 1 : addRecord(record, File);
				 break;
		case 2 : displayRecord(record, File);
				 break;
		case 3 : changeRecord(record, File);
	}
	sumCost(record,File);

	File.close();
	return 0;
}


void addRecord(Inven &record, fstream &File)
{
	File.seekp(0L, ios::end);
	cout << "Nhập thông tin hàng tồn kho sau:\n";
	cout << "Mô tả món hàng: ";
	cin.ignore();
	getline(cin, record.Desc);
	do
	{
		cout << "Ngày được thêm vào kho MM/DD/YYYY: ";
		cin.ignore();
		getline(cin, record.Date);

		if (validDate(record.Date) == 0)
		{
			cout << validDate(record.Date) << endl;
			cout << "Error! Định dạng ngày tháng ko hợp lệ.\n";
		}

	} while (validDate(record.Date) == 0);
	do
	{
		cout << "Số lượng :";
		cin  >> record.Qty;
		if (record.Qty < 0)
			displayError();
	} while (record.Qty < 0);
	do
	{
		cout << "Chi phí bán buôn: ";
		cin  >> record.WhsleCost;
		if (record.Qty < 0)
			displayError();
	} while (record.WhsleCost < 0);
	do
	{
		cout << "Chi phí bán lẻ: ";
		cin  >> record.RetailCost;
		if (record.RetailCost < 0)
			displayError();
	} while (record.RetailCost < 0);
	File.write(reinterpret_cast<char *>(&record), sizeof(record));
}


void displayRecord(Inven &record, fstream &File)
{
	int recNum;

	cout << "Nhập số hồ sơ: ";
	cin  >> recNum;
	if (recNum < 1)
		recNum = 1;
	recNum--;
	File.seekg(byteNum(recNum), ios::beg);
	File.read(reinterpret_cast<char *>(&record), sizeof(record));
	cout << "Record number: " << (recNum + 1) << endl;
	cout << "Mô tả món hàng: ";
	cout << record.Desc << endl;
	cout << "Date : ";
	cout << record.Date << endl;
	cout << "Số lượng  :";
	cout << fixed << showpoint << setprecision(2);
	cout << record.Qty << endl;
	cout << "Chi phí bán buôn: ";
	cout << record.WhsleCost << endl;
	cout << "Chi phí bán lẻ: ";
	cout << record.RetailCost << endl;
}

void changeRecord(Inven &record, fstream &File)
{
	int recNum;

	cout << "Nhập số hồ sơ: ";
	cin  >> recNum;
	if (recNum < 1)
		recNum = 1;
	recNum--;
	File.seekg(byteNum(recNum), ios::beg);
	File.read(reinterpret_cast<char *>(&record), sizeof(record));
	cout << "Nhập thông tin hàng tồn kho sau:\n";
	cout << "Mô tả món hàng: ";
	cin.ignore();
	getline(cin, record.Desc);
	do
	{
		cout << "Ngày được thêm vào kho MM/DD/YYYY: ";
		cin.ignore();
		getline(cin, record.Date);
		if (!validDate(record.Date))
		{
			cout << validDate(record.Date) << endl;
			cout << "Error!  Định dạng ngày tháng ko hợp lệ.\n";
		}
	} while (!validDate(record.Date));
	do
	{
		cout << "So luong :";
		cin  >> record.Qty;
		if (record.Qty < 0)
			displayError();
	} while (record.Qty < 0);
	do
	{
		cout << "Chi phí bán buôn: ";
		cin  >> record.WhsleCost;
		if (record.Qty < 0)
			displayError();
	} while (record.WhsleCost < 0);
	do
	{
		cout << "Chi phí bán lẻ: ";
		cin  >> record.RetailCost;
		if (record.RetailCost < 0)
			displayError();
	} while (record.RetailCost < 0);
	File.seekp(byteNum(recNum), ios::beg);
	File.write(reinterpret_cast<char *>(&record), sizeof(record));
}


long byteNum(int recNum)
{
	return sizeof(Inven) * recNum;
}


void displayError()
{
	cout << "Error! Số phải lớn hơn 0\n";
}

bool validDate(string date)
{
	if ( date.length() == 9)
		date = "0" + date;

	if (date.length() != 10)
		return false;

	for (int i = 0; i < date.length(); i++)
	{
		if (i == 2 || i == 5)
		{
			if (date[i] != '/')
			{
				return false;
			}
			continue;
		}

		if (!isdigit(date[i]))
			return false;
	}
	return true;
}

void sumCost(Inven &record, fstream &File){
    double Totwhsle  = 0,
		   TotRetail = 0;	
	int TotQty = 0;	
    while (!File.fail())
	{
		Totwhsle += record.WhsleCost * record.Qty;
		TotRetail += record.RetailCost * record.Qty;
		TotQty += record.Qty;
		File.read(reinterpret_cast<char *>(&record), sizeof(record));
	}
	File.close();
	cout << fixed << showpoint << setprecision(2);
	cout << "Tổng giá trị bán buôn của hàng tồn kho:       $"
		 << setw(10) << Totwhsle << endl;
	cout << "Tổng giá trị bán lẻ của hàng tồn kho:          $"
		 << setw(10) << TotRetail << endl;
	cout << "Tổng số lượng của tất cả các mặt hàng trong kho: $"
		 << setw(10) << TotQty << endl;
}
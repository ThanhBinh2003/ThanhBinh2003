#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

void dem(int *row, int row2)
{
	FILE *f = fopen("dssv.csv", "r");
	FILE *f1 = fopen("dsmh.csv", "r");
	FILE *f2 = fopen("diem.csv", "r");
	FILE *f3 = fopen("log.txt", "w");
	char a[1024];
	row,row2 = 0;
	int row1 = 0;
	while (!feof(f))
	{
		fgets(a, 1024, f);
		*row +=1;
	}
	while (!feof(f1))
	{
		fgets(a, 1024, f1);
		row1 ++;
	}
	while (!feof(f2))
	{
		fgets(a, 1024, f2);
		row2 +=1;
	}
	int b = *row;
	int c = row2;
	fprintf(f3, "%d %d %d", b-1, row1, c-1);
}
void lenh1(char fn[], char f2[]) // in danh sách sinh viên lớp cần tìm
{
	strcat(fn, "/dssv.csv");
	FILE *f= fopen(fn, "r");
	FILE *f1 = fopen(f2, "w");
	if(!f)
	{
		FILE * f3 = fopen("result.csv", "w");
		exit (0);	
	}
	else
	{
		char a[1024];
		int row = 0;
		while(fgets(a, 1024,f) ){
			row ++;
			if(row == 1)
			continue;
			{
				fprintf(f1, "%s", a);
			}
		}
		fclose(f);
		fclose(f1);
	}
}
void countmale(char fn[], char f2[]) // đếm nam 
{
	FILE * f = fopen(fn, "r");
	FILE * f1 = fopen(f2, "w");
	int s = 0;
	char a[1024];
	while(fgets(a, 1024, f) )
	{
		char *value = strtok(a, ",");
		while(value)
		{
			if(strcmp(value, "Male") == 0)
		    s ++;
		    value = strtok(NULL,",");
		}		
	}
	fprintf(f1, "%d", s);
	fclose(f);
	fclose(f1);
}
void countfemale(char fn[], char f2[]) // đếm nữ
{
	FILE * f = fopen(fn, "r");
	FILE * f1 = fopen(f2, "w");
	int s = 0;
	char a[1024];
	while(fgets(a, 1024, f) )
	{
		char *value = strtok(a, ",");
		while(value)
		{
			if(strcmp(value, "Female") == 0)
		    s ++;
		    value = strtok(NULL,",");
		}		
	}
	fprintf(f1, "%d", s);
	fclose(f);
	fclose(f1);
}
//5:
void country(char fn[],char f2[], char s[]) // tìm sinh viên thuộc các nước
{
	FILE *f = fopen(fn, "r");
	FILE *f1 = fopen(f2, "w");
	char a[1024], b[1024];
	int i;
	s[0]=toupper(s[0]); // viết hoa ký tự đầu
	for(i=1;i<strlen(s);i++)
	{
		s[i]=tolower(s[i]); // viết hoa các ký tự tiếp theo
	}
	strcat(s,"\n"); // vì cuối nước có kí tự xuống dòng nên chèn thêm kí tự đó 
	fgets(a, 1024, f);
	while(fgets(a, 1024, f) )
	{
		strcpy(b, a);
		char *value = strtok(a, ",");
		while(value)
		{
			if(strcmp(value,s) == 0  )
		    fprintf( f1,"%s", b);
		    value = strtok(NULL,",");    
		}		
	}
	fclose(f);
	fclose(f1);
}

//lenh3:
struct SinhVien{
	char MSSV[ 100];
	char firstn[100];
	char lastn[100];
	char gender[100];
	char NgaySinh[100];
	char clasnme[100];
	char country[100];
	float diemtb;
	int dem;
	int sapxep;
	
};
//lua file vao struct
void luafile(struct SinhVien sv[], char fn[], int row) // lưa file dssv vào struct 
{
	FILE * f = fopen(fn, "r");
	int s = 0;
	char a[1024];
	int i;
	for (i = 0;i<row;i++)
	{
	while(fgets(a, 1024, f))
	{
		char *tmp = strtok(a, ",");
		while(tmp)
		{
        	strcpy(sv[i].MSSV, tmp);
			break;	
		}
		while(tmp)
		{
			tmp = strtok(NULL, ",");
        	strcpy(sv[i].firstn, tmp);
        	break;
		}
		while(tmp)
        {
        	tmp = strtok(NULL, ",");
        	strcpy(sv[i].lastn, tmp);
        	break;
		}
		while(tmp)
		{
			tmp = strtok(NULL, ",");
            strcpy(sv[i].gender, tmp);
            break;
		}    
		while(tmp)
		{
			tmp = strtok(NULL, ",");
            strcpy(sv[i].NgaySinh, tmp);
            break;
		}    
		while(tmp)
		{
			tmp = strtok(NULL, ",");
            strcpy(sv[i].clasnme, tmp);
            break;
		}    
		while(tmp)
		{
			tmp = strtok(NULL, ",");
            strcpy(sv[i].country, tmp);
            break;
		}  
		i++;  	
    }
    strcat(sv[row-1].country, "\n"); // cho dòng cuối 1 ký tự xuống dòng
    }
    fclose(f);
}
//sap xep theo tang dan
void th(struct SinhVien sv[], int row)
{
	FILE *f2 = fopen("result.csv", "w");
	struct SinhVien temp;
	int i,j;
    for(i = 1; i<row;i++)
   {
   	char *b;
   	strcpy(b, sv[i].NgaySinh);
   	char *a = strtok(b, "/");
   	sv[i].sapxep = atoi(a)* 100;
   	a = strtok(NULL, "/");
   	sv[i].sapxep += atoi(a) * 20;
   	a = strtok(NULL, "/");
   	sv[i].sapxep += atoi(a);
   }
   for(i=1;i<row-1;i++)
    for(j=i+1;j<row;j++)
    {
    		if(strcmp(sv[i].firstn,sv[j].firstn) >0 )
         {
            temp = sv[i];
            sv[i] = sv[j];
            sv[j] = temp;
         }
        if(strcmp(sv[i].firstn,sv[j].firstn) == 0)
        {
        	if(sv[i].sapxep > sv[j].sapxep)
        	{
        	temp = sv[i];
            sv[i] = sv[j];
            sv[j] = temp;
			}
		}
        if(strcmp(sv[i].firstn,sv[j].firstn) == 0 && sv[i].sapxep == sv[j].sapxep)
        {
        	if(strcmp(sv[i].lastn,sv[j].lastn) >0 )
         {
            temp = sv[i];
            sv[i] = sv[j];
            sv[j] = temp;
         }
		}
		if(strcmp(sv[i].firstn,sv[j].firstn) == 0 && sv[i].sapxep == sv[j].sapxep && strcmp(sv[i].lastn,sv[j].lastn) == 0)
		{
			if(strcmp(sv[i].country,sv[j].country) > 0 )
         {
            temp = sv[i];
            sv[i] = sv[j];
            sv[j] = temp;
         }
		}
	}
		
}
//in theo thu tu tang dan
void in(struct SinhVien sv[], int row)
{
	FILE *f2 = fopen("result.csv", "w");
	int len = strlen(sv[row-1].country);
	sv[row-1].country[len-1] = '\0';
	int i;
	for(i = 1; i<row; i++)
    {
    	fprintf(f2, "%s,%s,%s,%s,%s,%s,%s", sv[i].MSSV, sv[i].firstn, sv[i].lastn, sv[i].gender, sv[i].NgaySinh, sv[i].clasnme, sv[i].country);
	}
}
//in theo thu tu giam dan
void in2(struct SinhVien sv[], int row)
{
	FILE *f2 = fopen("result.csv", "w");
	int len = strlen(sv[1].country); // gán kỳ tự null vào hàng cuối để không in dư dấu xuống xòng
	sv[1].country[len-1] = '\0';
	int i;
	for(i = row-1; i>=1; i--)
    {
    	fprintf(f2, "%s,%s,%s,%s,%s,%s,%s", sv[i].MSSV, sv[i].firstn, sv[i].lastn, sv[i].gender, sv[i].NgaySinh, sv[i].clasnme, sv[i].country);
	}
}
//tìm mssv giống với mssv trong dssv và cộng lại
void tim_mssv(struct SinhVien sv[],int row, char mssv[], float diem)
{
	int i;
  for(i = 0; i< row; i++)
  {
		if(strcmp(sv[i].MSSV, mssv) == 0)
			{
				sv[i].diemtb += diem;
				sv[i].dem += 1;
			}
  }
  
}
//top n
void top(struct SinhVien sv[], int row, int row2) // sắp xếp top từ cao xuống thấp
{
    FILE * f = fopen("diem.csv", "r");
    FILE *f2 = fopen("diem.csv", "r");
    char a[1024];
    while (!feof(f2))
	{
		fgets(a, 1024, f2);
		row2 +=1;
	}
	row2-=1;
	int i, j;
	char mssv[100];
	fgets(a, 1024, f);
	for (i = 0;i<row2;i++)
	{
		while(fgets(a, 1024, f))
		{
			char *tmp = strtok(a, ",");
			while(tmp)
			{
	        	strcpy(mssv, tmp);
				break;	
			}
			while(tmp)
			{
				tmp = strtok(NULL, ",");
	        	break;
			}
			while(tmp)
	        {
	        	tmp = strtok(NULL, ",");
	        	float b = atof(tmp);
            	tim_mssv(sv,row,mssv, b);
	        	break;
			}
			i++;
		}
	}
	for(i=0;i<row;i++)
	{
		sv[i].diemtb = (float)sv[i].diemtb / sv[i].dem;
	}
	fclose(f);
	struct SinhVien temp; // tọa một struct tạm 
	for(i=1;i<row-1;i++)
	    for(j=i+1;j<row;j++)
	    {
	    		if( sv[i].diemtb < sv[j].diemtb )
		         {
		            temp = sv[i];
		            sv[i] = sv[j];
		            sv[j] = temp;
		         }
	        	if(sv[i].diemtb == sv[j].diemtb )
			        {
			        	if(strcmp(sv[i].firstn,sv[j].firstn) >0)
			        	{
			        	temp = sv[i];
			            sv[i] = sv[j];
			            sv[j] = temp;
						}
					}
				if(sv[i].diemtb == sv[j].diemtb && strcmp(sv[i].firstn,sv[j].firstn) == 0 )
			        {
			        	if(strcmp(sv[i].lastn,sv[j].lastn) > 0)
			        	{
			        	temp = sv[i];
			            sv[i] = sv[j];
			            sv[j] = temp;
						}
					}
		}	
}
// in top n
void in3(struct SinhVien sv[], int n)
{
	FILE *f = fopen("result.csv", "w");
	int len = strlen(sv[n].country);
	sv[n].country[len-1] = '\0';
	int i;
	for(i=1;i<=n;i++)
	{
		fprintf(f ,"%s,%s,%s,%s,%s,%s,%s", sv[i].MSSV, sv[i].firstn, sv[i].lastn, sv[i].gender, sv[i].NgaySinh, sv[i].clasnme, sv[i].country);
	}
	fclose(f);
}
// tạo một chương trình tạo file lỗi 
void caulenhloi()
{
	FILE *f = fopen("errol.txt", "w");
	fprintf(f, "invalid comand");
}
int main()
{
	int row, row2;
	dem(&row, row2);
	row = row-1;
	struct SinhVien sv[300];
	luafile(sv, "dssv.csv", row);
	//so dong
	char s[50];
	printf("Nhap lenh:");
	gets(s);
	char *caulenh1, *dich1, caulenh[20], dich[20];
	caulenh1 = strtok(s, " ");
	dich1 = strtok(NULL, " ");
	strcpy(caulenh, caulenh1);
	strcpy(dich, dich1);
	int i;
	for(i=0;i<strlen(caulenh); i++)
    {
        caulenh[i] = tolower(caulenh[i]);
    }
    for(i=0;i<strlen(dich); i++)
    {
        dich[i] = tolower(dich[i]);
    }
	//lenh1:
	if(strcmp(caulenh, "list") == 0 )	
	{
		lenh1(dich, "result.csv");
	}
	//lenh2:
	if(strcmp(caulenh, "count") == 0)
	{
		if(strcmp(dich, "male") == 0)
		{
			countmale("dssv.csv", "result.csv");
		}
		if(strcmp(dich, "female") == 0)
		{
			countfemale("dssv.csv", "result.csv");
		}
		else 
		caulenhloi();
	}
	//lenh5:
	if(strcmp(caulenh, "country") == 0)
	{
		country("dssv.csv", "result.csv", dich);
	}
	//lenh4:
	if(strcmp(caulenh, "sort") == 0)
	{
		if(strcmp(dich, "acs") == 0)
		{
			th(sv, row);
			in(sv, row);
		}
		if(strcmp(dich, "decs") == 0)
		{
			th(sv, row);
			in2(sv, row);
		}
		else 
		caulenhloi();
	}
	//lenh 3	
	if(strcmp(caulenh, "top") == 0)
	{
		for(i=0;i<strlen(dich);i++)
		{
		if(dich[i] < '0' || dich[i] >'9')
		caulenhloi();
		}
		int n = atoi(dich);
		if(n<=0)
		caulenhloi();
		if(n>0)
		{
			top(sv, row, row2);
			in3(sv, n);
		}
	}
	else
	{
		caulenhloi();
	}
	return 0;
}
#include <iostream>
#define N 40

class Square
{
private:
	int  **s_array;
	int  *x;
	int  *y;
	int  *w;  //длины сторон
  int  size;
	int  s_amount;  //количество квадратов
	int  num;  //порядковый номер квадрата
	bool if_last;  //послдений ли квадарт

	void set_square(int x, int y, int n, int side);
	void set_second();
	void set_third();
	bool is_empty(int &x, int &y);
	int  get_max_size(int x, int y);
	void delete_square(int x, int y, int side);

public:
	Square(int size);
	int  set_first();
	void result(int amount);
	int  backtracking(int deep);
	~Square();
};

Square::Square(int size) : size(size)
{
	s_array= new int*[size];
	for(int i=0; i<size; i++)
	{
		s_array[i]= new int[size];
		for(int j=0; j<size; j++)
			s_array[i][j]=0;
	}
	s_amount= N;
	x= new int[N];
	y= new int[N];
	w= new int[N];
	if_last=false;
	num=0;
}

void Square::set_square(int x, int y, int n, int side)
{
	for(int i=x; i < x+side; i++)
		for(int j=y; j < y+side; j++)
			s_array[i][j] = n;
}

int Square::set_first()
{
	x[num]=y[num]=0;
	if(size%2 == 0)
	{
		x[2]=y[1]=0;
		x[1]=x[3]=y[2]=y[3]=size*1/2;
		for(int i=0; i<4; i++)
			w[i]=size*1/2;
		return 4;
	}
	if(size%3 == 0)
	{
		w[num]=size*2/3;
		x[4]=y[1]=0;
		x[5]=y[2]=w[num]*1/2;
		x[1]=x[2]=x[3]=y[3]=y[5]=y[4]=w[num];
		for(int i=1; i<6; i++)
			w[i]=size*1/3;
		return 6;
	}
	if(size%5 == 0)
	{
		w[num]=size*3/5;
		x[4]=y[1]=0;
		w[2]=w[3]=w[5]=w[6]=w[num]*1/3;
		w[1]=w[4]=w[7]=w[num]*2/3;
		x[5]=x[6]=y[2]=y[3]=size*2/5;
		x[3]=y[6]=size*4/5;
		x[1]=x[2]=x[7]=y[4]=y[5]=y[7]=w[num];
		return 8;
	}
	else
	{
		w[num]=size*1/2 + 1;
		set_square(x[num], y[num], num+1, w[num]);
		num++;
		set_second();
		set_third();
		return backtracking(4);
	}
}

void Square::set_second()
{
	x[num]=w[0];
	y[num]=0;
	w[num]=get_max_size(x[num], y[num]);
	set_square(x[num], y[num], num+1, w[num]);
	num++;
}

void Square::set_third()
{
	x[num]=0;
	y[num]=w[0];
	w[num]=get_max_size(x[num], y[num]);
	set_square(x[num], y[num], num+1, w[num]);
	num++;
}

void Square::delete_square(int x, int y, int side)
{
	for(int i=x; i < x+side; i++)
		for(int j=y; j < y+side; j++)
			s_array[i][j] = 0;
}

bool Square::is_empty(int &x, int &y)
{
	for(int i=0; i < size; i++)
		for(int j=0; j < size; j++)
			if(!s_array[i][j])
			{
				x=i;
				y=j;
				return true;
			}
	return false;
}

int Square::get_max_size(int x, int y)
{
	int max_size=1, size1=0, size2=0, i=0, j=0;
	while(i < size-x && s_array[x+i][y] == 0)
	{
		size1++;
		i++;
	}
	while(j < size-y && s_array[x][y+j] == 0)
	{
		size2++;
		j++;
	}
	(size1 < size2) ? (max_size = size1) : (max_size = size2);
	return max_size;
}

int Square::backtracking(int deep)
{
	if(if_last && deep > num)
		return deep;
  int x_tmp;
	int y_tmp;
	int w_tmp;
	int result_tmp;
	int min_result=size*size;
	if(!is_empty(x_tmp, y_tmp))
	{
		if((if_last && deep-1 < num) || !if_last)
			num=deep-1;
		if_last=true;
	  return num;
	}
	for(w_tmp=get_max_size(x_tmp, y_tmp); w_tmp>0; w_tmp--)
	{
		set_square(x_tmp, y_tmp, deep, w_tmp);
		result_tmp = backtracking(deep+1);
		min_result = min_result < result_tmp ? min_result : result_tmp;
		if(result_tmp<=num)
		{
			x[deep-1] = x_tmp;
			y[deep-1] = y_tmp;
			w[deep-1] = w_tmp;
		}
		delete_square(x_tmp, y_tmp, w_tmp);
	}
	return min_result;
}

void Square::result(int amount)
{
	std::cout<<amount<<"\n";
	for(int i=0; i<amount; i++)
		std::cout<<x[i]+1<<" "<<y[i]+1<<" "<<w[i]<<"\n";
}

Square::~Square()
{
	delete[] x;
	delete[] y;
	delete[] w;
	for(int i=0; i<size; i++)
		delete[] s_array[i];
	delete[] s_array;
}

int main()
{
	int size, s_amount;
	std::cin>>size;
	Square table(size);
	s_amount=table.set_first();
	table.result(s_amount);
	return 0;
}

#pragma once
#include <vector>
#include <iostream>
#include <iomanip>

class Matrixf
{
public:
	Matrixf(int n, int m) : height(n), width(m)
	{
		std::vector<float> zeroLine(width, 0);

		data.assign(height, zeroLine);
	}

	int getHeight() const
	{
		return height;
	}

	int getWidth() const
	{
		return width;
	}

	const std::vector<float>& operator[](int index) const
	{
		return data[index];
	}

	std::vector<float>& operator[](int index)
	{
		return data[index];
	}

	std::vector<float> getColumn(int index)
	{
		std::vector<float> column(height);
		for (int i = 0; i < height; i++)
		{
			column[i] = data[i][index];
		}
		
		return column;
	}

private:
	int height, width;
	std::vector<std::vector<float>> data;
};

void show(const Matrixf& matrix)
{
	std::cout << std::setprecision(3);

	for (int i = 0; i < matrix.getHeight(); i++)
	{
		std::cout << "[ ";

		for (int j = 0; j < matrix.getWidth(); j++)
		{
			std::cout << matrix[i][j] << " ";
		}

		std::cout << "]" << std::endl;
	}
}

void show(const std::vector<float>& vec)
{
	std::cout << std::setprecision(3) << "[ ";

	for (float x : vec)
	{
		std::cout << x << ' ';
	}

	std::cout << "]" << std::endl;
}

float dot(const std::vector<float>& a, const std::vector<float>& b)
{
	float s = 0;
	for (int i = 0; i < a.size(); i++)
	{
		s += a[i] * b[i];
	}

	return s;
}
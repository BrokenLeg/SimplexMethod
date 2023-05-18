#include "Matrix.h"

const float M = 1.0E+08;

int main()
{
	std::vector<float> p = {2, -3, 3, 0, 0, 0, -M, -M};

	Matrixf A(3, 8);

	A[0] = { -1, 5, -5, -1, 0, 0, 1, 0 };
	A[1] = { 5, 4, -4,  0, 1, 0, 0, 0 };
	A[2] = {-7, 2, -2, 0, 0, -1, 0, 1 };

	std::vector<float> c = { -M, 0, -M };
	std::vector<float> b = { 5, 28, 0 };

	float f = dot(c, b);

	std::vector<float> n = { 6, 4, 7 };

	std::vector<float> z = { 0, 0, 0, 0, 0, 0, 0, 0};
	std::vector<float> q = { 0, 0, 0 };

	bool finished = false;
	
	while (true)
	{
		int pivot = -1;
		float max = -1;

		for (int i = 0; i < z.size(); i++)
		{
			z[i] = p[i] - dot(c, A.getColumn(i));
			if (z[i] > 0 && z[i] > max)
			{
				max = z[i];
				pivot = i;
			}
		}

		f = dot(c, b);

		{
			std::cout << "F = " << f << std::endl;
			std::cout << "C: "; show(c);
			std::cout << "N: "; show(n);
			std::cout << "B: "; show(b);
			std::cout << "Q: "; show(q);
			std::cout << "Z: "; show(z);

			std::cout << std::endl << "Constraints matrix" << std::endl;
			show(A);
			std::cout << std::endl;
		}

		if (pivot == -1)
		{
			std::cout << "Found maximum : " << f << std::endl;
			break;
		}

		std::cout << "New basis : " << pivot + 1 << std::endl;

		int exclude = -1;
		float min = 100000;

		int zeroExclude = -1;

		for (int i = 0; i < q.size(); i++)
		{
			bool isNegative = (A[i][pivot] < 0);

			q[i] = b[i] / A[i][pivot];

			if (!isNegative && q[i] >= 0 && q[i] < min)
			{
				min = q[i];
				exclude = i;
			}
		}

		if (exclude == -1)
		{
			exclude = zeroExclude;
		}

		std::cout << "Q: "; show(q);

		if (exclude == -1)
		{
			std::cout << "No maximum" << std::endl;
			break;
		}

		std::cout << "Exclude : " << exclude + 1 << std::endl;

		n[exclude] = pivot;
		c[exclude] = p[pivot];

		float b_exclude = b[exclude];

		for (int i = 0; i < b.size(); i++)
		{
			float k = A[i][pivot] / A[exclude][pivot];

			if (i == exclude)
			{
				b[i] = b[i] / A[exclude][pivot];
			}
			else
			{
				b[i] = b[i] - k * b_exclude;
			}
		}

		float t = A[exclude][pivot];


		for (int i = 0; i < A.getHeight(); i++)
		{
			float k = A[i][pivot] / A[exclude][pivot];

			for (int j = 0; j < A.getWidth(); j++)
			{
				if (i == exclude)
				{
					A[i][j] = A[i][j] / t;
				}
				else
				{
					A[i][j] = A[i][j] - k * A[exclude][j];
				}
			}
		}

		//break;
	}

	return 0;
}
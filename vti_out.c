#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <stdlib.h>

int vti_out(
	int nx, int ny, int nz, // x方向y方向z方向のデータ数
	int origin_x, int origin_y, int origin_z, // x方向y方向z方向のデータ数
	float *data,            // float型三次元配列へのポインタ
	FILE *stream           // 出力先ストリーム(fopenで開いたファイルディスクリプタへのポインタなど)
	)
{

	int test_endi=1;
	int i, j, k;

	const unsigned count = (unsigned)(sizeof(float) * nx * ny * nz);

	fprintf(stream, "<?xml version=\"1.0\"?>\n");
	if (*(char*)&test_endi)
	{
		fprintf(stream, "<VTKFile type=\"ImageData\" version=\"0.1\" byte_order=\"LittleEndian\" header_type=\"UInt32\">\n");
	}
	else
	{
		fprintf(stream, "<VTKFile type=\"ImageData\" version=\"0.1\" byte_order=\"BigEndian\" header_type=\"UInt32\">\n");
	}
	fprintf(stream, "<ImageData WholeExtent=\"0 %d 0 %d 0 %d\" Origin=\"%d %d %d\" Spacing=\"1 1 1\">\n", nx - 1, ny - 1, nz - 1, origin_x, origin_y, origin_z);
	fprintf(stream, "<Piece Extent=\"0 %d 0 %d 0 %d\">\n", nx - 1, ny - 1, nz - 1);
	fprintf(stream, "<PointData Scalars=\"ImageScalars\">\n");
	fprintf(stream, "<DataArray type=\"Float32\" Name=\"SampleScalars\" format=\"appended\" RangeMin=\"-10\" RangeMax=\"100\" offset=\"0\"/>\n");
	fprintf(stream, "</PointData>\n");
	fprintf(stream, "<CellData>\n");
	fprintf(stream, "</CellData>\n");
	fprintf(stream, "</Piece>\n");
	fprintf(stream, "</ImageData>\n");
	fprintf(stream, "<AppendedData encoding=\"raw\">\n");
	fprintf(stream, "_");


	fwrite(&count, sizeof(unsigned), 1, stream);
	for (k = 0; k < nz; k++)
	{
		for (j = 0; j < ny; j++)
		{
			for (i = 0; i < nx; i++)
			{
				fwrite(&data[nx * ny * k + nx * j + i], sizeof(float), 1, stream);
			}
		}
	}

	fprintf(stream, "\n</AppendedData>\n");
	fprintf(stream, "</VTKFile>\n");

	return 0;
}


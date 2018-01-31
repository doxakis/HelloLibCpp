using OpenCvSharp;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace CSharpAndCpp
{
	public static class NativeTest
	{
		private const string DllFilePath = @"HelloLibCpp.dll";

		[DllImport(DllFilePath, CallingConvention = CallingConvention.Cdecl)]
		private extern static int parseFileCpp(int[] arr, int length, int pos);

		[DllImport(DllFilePath, CallingConvention = CallingConvention.Cdecl)]
		private extern static int parseFileC(int[] arr, int length, int pos);
		
		public static int ParseFileCpp(int[] arr, int pos)
		{
			return parseFileCpp(arr, arr.Length, pos);
		}

		public static int ParseFileC(int[] arr, int pos)
		{
			return parseFileC(arr, arr.Length, pos);
		}
	}

	class Program
	{
		static void Main(string[] args)
		{
			int n = 10000000;

			int[] arr;
			using (Mat src = new Mat("form9.jpg", ImreadModes.GrayScale))
			{
				arr = new int[src.Width * src.Height];

				using (MatOfByte mat = new MatOfByte(src))
				{
					MatIndexer<byte> indexer = mat.GetIndexer();
					int i = 0;
					for (int y = 0; y < src.Height; y++)
					{
						for (int x = 0; x < src.Width; x++)
						{
							arr[i] = indexer[y, x];
							i++;
						}
					}
				}
			}

			// Testing multi-thread.
			Parallel.For(0, n, new ParallelOptions { MaxDegreeOfParallelism = Environment.ProcessorCount }, i =>
			{
				var resultCpp = NativeTest.ParseFileCpp(arr, i);
				Console.WriteLine("Result from cpp: " + resultCpp);

				var resultC = NativeTest.ParseFileCpp(arr, i);
				Console.WriteLine("Result from c: " + resultC);

				Thread.Sleep(100);
			});
			
			Console.WriteLine("Press any key to continue...");
			Console.ReadLine();
		}
	}
}

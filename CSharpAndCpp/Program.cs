using OpenCvSharp;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace CSharpAndCpp
{
	public static class NativeTest
	{
		private const string DllFilePath = @"HelloLibCpp.dll";

		[DllImport(DllFilePath, CallingConvention = CallingConvention.Cdecl)]
		private extern static int parseFileCpp(byte[] arr, int length);

		[DllImport(DllFilePath, CallingConvention = CallingConvention.Cdecl)]
		private extern static int parseFileC(byte[] arr, int length);

		public static int ParseFileCpp(byte[] arr)
		{
			return parseFileCpp(arr, arr.Length);
		}

		public static int ParseFileC(byte[] arr)
		{
			return parseFileC(arr, arr.Length);
		}
	}

	class Program
	{
		static void Main(string[] args)
		{
			byte[] arr;
			using (Mat src = new Mat("form9.jpg", ImreadModes.GrayScale))
			{
				arr = new byte[src.Width * src.Height];

				using (MatOfByte mat = new MatOfByte(src))
				{
					MatIndexer<byte> indexer = mat.GetIndexer();
					for (int y = 0; y < src.Height; y++)
					{
						for (int x = 0; x < src.Width; x++)
						{
							arr[y * src.Width + x] = indexer[y, x];
						}
					}
				}
			}
			
			Console.WriteLine("Calling cpp");
			var resultCpp = NativeTest.ParseFileCpp(arr);
			Console.WriteLine("Result from cpp: " + resultCpp);
			
			Console.WriteLine("Calling c");
			var resultC = NativeTest.ParseFileCpp(arr);
			Console.WriteLine("Result from c: " + resultC);
			
			Console.WriteLine("Press any key to continue...");
			Console.ReadLine();
		}
	}
}

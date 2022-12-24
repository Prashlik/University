using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Collections;

namespace LabWork2
{
	class Cluster
	{
		List<ImageObject> scores = new List<ImageObject>();
		List<float> values = new List<float>();

		public float curV;
		public float lastV;
		public int Size() { return scores.Count(); }
		void Add(ImageObject s, float v) { scores.Add(s); values.Add(v); }
		void SetCenter()
		{
			float sumV = 0;
			int size = Size();
			for (int i = 0; i < size; sumV += values[i], i++) ;
			lastV = curV;
			curV = sumV / size;
		}
		void Clear()
		{
			scores.Clear();
			values.Clear();
		}
		static Cluster[] Bind(int k, Cluster[] clusarr, List<ImageObject> sc, List<List<float>> val)
		{
			for (int j = 0; j < k; j++)
				clusarr[j].Clear();
			int size = sc.Count();
			for (int i = 0; i < size; i++)
			{
				float temp = 0;
				for (int a = 0; a < val.Count(); a++)
					temp += (float)Math.Pow(val[a][i], 2);
				temp = (float)Math.Sqrt(temp);

				float min = Math.Abs(clusarr[0].curV - temp);
				Cluster cl = clusarr[0];
				for (int j = 1; j < k; j++)
				{
					float tmp = Math.Abs(clusarr[j].curV - temp);
					if (min > tmp) { min = tmp; cl = clusarr[j]; }
				}
				cl.Add(sc[i], temp);
			}
			return clusarr;
		}
		static void InitialCenter(int k, Cluster[] clusarr, List<List<float>> val)
		{
			int size = val[0].Count();
			int step = size / k;
			int steper = 0;

			for (int i = 0; i < k; i++, steper += step)
			{
				float temp = 0;
				for (int j = 0; j < val.Count(); j++)
					temp += (float)Math.Pow(val[j][steper], 2);
				clusarr[i].curV = (float)Math.Sqrt(temp);
			}
		}
		public static void Start(int k, Cluster[] clusarr, List<ImageObject> sc, List<List<float>> val)
		{
			InitialCenter(k, clusarr, val);
			for (; ; )
			{
				int chk = 0;
				Bind(k, clusarr, sc, val);
				for (int j = 0; j < k; j++)
					clusarr[j].SetCenter();
				for (int p = 0; p < k; p++)
					if (clusarr[p].curV == clusarr[p].lastV)
						chk++;
				if (chk == k) return;
			}
		}
		public List<ImageObject> at() { return scores; }
	};
}

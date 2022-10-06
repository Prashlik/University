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
	struct POINT
	{ 
		public int x, y;
		public POINT(int x, int y)
		{
			this.x = x;
			this.y = y;
		} 
	}
	class Cluster
	{
		List<POINT> scores = new List<POINT>();
		public int curX, curY;//координаты текущего центроида
		public int lastX, lastY;//координаты предыдущего центоида
		public int Size() { return scores.Count(); }//получаем размер списка
		void Add(POINT pt) { scores.Add(pt); }//Добавляем пиксель к кластеру
		void SetCenter()
		{
			int sumX = 0, sumY = 0;
			int i = 0;
			int size = Size();
			for (; i < size; sumX += scores[i].x, i++) ;//the centers of mass by x
			i = 0;
			for (; i < size; sumY += scores[i].y, i++) ;//the centers of mass by y
			lastX = curX;
			lastY = curY;
			curX = sumX / size;
			curY = sumY / size;
		}
		void Clear()
		{
			scores.Clear();
		}
		static Cluster[] Bind(int k, Cluster[] clusarr, List<POINT> vpt)
		{
			for (int j = 0; j < k; j++)
				clusarr[j].Clear();// Чистим кластер перед использованием
			int size = vpt.Count();
			for (int i = 0; i < size; i++)
			{// Запускаем цикл по всем пикселям множества
				int min = (int)Math.Sqrt(
					Math.Pow((float)clusarr[0].curX - vpt[i].x, 2) + Math.Pow((float)clusarr[0].curY - vpt[i].y, 2)
					);
				Cluster cl = clusarr[0];
				for (int j = 1; j < k; j++)
				{
					int tmp = (int)Math.Sqrt(
						Math.Pow((float)clusarr[j].curX - vpt[i].x, 2) + Math.Pow((float)clusarr[j].curY - vpt[i].y, 2)
						);
					if (min > tmp) { min = tmp; cl = clusarr[j]; }// Ищем близлежащий кластер
				}
				cl.Add(vpt[i]);// Добавляем в близ лежащий кластер текущий пиксель
			}
			return clusarr;
		}
		static void InitialCenter(int k, Cluster[] clusarr, List<POINT> vpt)
		{

			int size = vpt.Count();
			int step = size / k;
			int steper = 0;

			for (int i = 0; i < k; i++, steper += step)
			{
				clusarr[i].curX = vpt[steper].x;
				clusarr[i].curY = vpt[steper].y;
			}
		}
		public static void Start(int k, Cluster[] clusarr, List<POINT> vpt)
		{
			InitialCenter(k, clusarr, vpt);
			for (; ; )
			{//Запускаем основной цикл
				int chk = 0;
				Bind(k, clusarr, vpt);//Связываем точки с кластерами
				for (int j = 0; j < k; j++)//Высчитываем новые координаты центроидов 
					clusarr[j].SetCenter();
				for (int p = 0; p < k; p++)//Проверяем не совпадают ли они с предыдущими цент-ми
					if (clusarr[p].curX == clusarr[p].lastX && clusarr[p].curY == clusarr[p].lastY)
						chk++;
				if (chk == k) return;//Если да выходим с цикла
			}
		}
		List<POINT> at(int i) { return scores; }//Доступ  к элементам вектора
	};
}

namespace LabWork8
{
    class Program
    {
        static void Main(string[] args)
        {
            Random_functions r = new Random_functions(); 
            Part_1 p1 = new Part_1();
            Part_2 p2 = new Part_2();
            Part_3_1 p3_1 = new Part_3_1();
            Part_3_2 p3_2 = new Part_3_2();

            Console.WriteLine("================ Лабораторная работа 8 ================");
            Console.WriteLine("--------------- Часть первая. Вариант 1 ---------------");
            Console.WriteLine("\nИспользуя заранее заготовленные числа (100 итераций):");

            p1.Run(r.Get_Prapared1(), r.Get_Prapared2(), r.Get_Prapared3());
            p1.Print_Result();
            p1.Clear();

            Console.WriteLine("\nИспользуя средства языка (1000х100 итераций):");

            for (int i = 0; i < 1000; i++)
                p1.Run(r.Get_System_Random(), r.Get_System_Random(), r.Get_System_Random());
            p1.Print_Result();
            p1.Clear();

            Console.WriteLine("\n--------------- Часть вторая. Вариант 1 ---------------");
            Console.WriteLine("\nИспользуя метод обратных функций:");

            p2.Run_1(r.Get_Prapared3());
            p2.Print_Result();
            p2.Clear();

            Console.WriteLine("\nИспользуя метод исключений:");

            p2.Run_2(r.Get_Prapared1(), r.Get_Prapared2());
            p2.Print_Result();
            p2.Clear();

            Console.WriteLine("\n--------------- Часть третья. Вариант 1 ---------------");
            Console.WriteLine("\nПервая часть:");

            for (int i = 0; i < 1000; i++)
                p3_1.Run(r.Get_System_Random());
            p3_1.Print_Result();
            p3_1.Clear();

            Console.WriteLine("\nВторая часть:");

            for (int i = 0; i < 1000; i++)
                p3_2.Run(r.Get_System_Random());
            p3_2.Print_Result();
            p3_2.Clear();
        }
    }

}
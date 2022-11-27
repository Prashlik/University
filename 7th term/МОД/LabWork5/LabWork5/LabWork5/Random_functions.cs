using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LabWork5
{
    internal class Random_functions
    {
        Random random = new Random();

        private const int a_Lehmer = 11817;
        private const int m_Lehmer = 100;
        private int prev_Lehmer = 7;

        private const int a_Congruent = 911;
        private const int m_Congruent = 100;
        private const int c_Congruent = 733;
        private int prev_Congruent = 7;


        public double System_Random()
        {
            return random.NextDouble();
        }

        public double Lehmer_Random()
        {
            prev_Lehmer = ((a_Lehmer * prev_Lehmer) % m_Lehmer);
            return (double)prev_Lehmer / 100;
        }

        public double Congruent_Random()
        {
            prev_Congruent = ((a_Congruent * prev_Congruent + c_Congruent) % m_Congruent);
            return (double)prev_Congruent / 100;
        }
    }
}

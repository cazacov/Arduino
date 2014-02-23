using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Mirror
{
    class Program
    {
        static void Main(string[] args)
        {
            int x0 = 0;
            int y0 = 0;

            var d = 15.0;
            var r = 40.0;

            var order = new int[] { 3, 6, 1, 8, 4, 5, 2, 7 };
            var delta = d * Math.Sin(16 * Math.PI / 180);
            Console.WriteLine(delta);

            for (int i = 0; i< 8; i++)
            {
                var phi0 = i * 45.0 * Math.PI / 180.0;
                var phi1 = (i + 1) * 45.0 * Math.PI / 180.0;
                
                var idx = order[i] + 2;


                var l = r - d * Math.Sin(idx * Math.PI / 180.0);

                Console.WriteLine("{0}-{1}\t{2:0.000}", i, idx, l);
                Console.WriteLine("{0:0.000}\t{1:0.000}", x0 + l * Math.Cos(phi0), y0 + l * Math.Sin(phi0));
                Console.WriteLine("{0:0.000}\t{1:0.000}", x0 + l * Math.Cos(phi1), y0 + l * Math.Sin(phi1));
                Console.WriteLine();
            }

            Console.ReadKey();
        }
    }
}

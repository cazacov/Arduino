using System;

namespace Mirror
{
    /*
     * Calculates 3D model coordinates of octogonal mirror
     */

    internal class Program
    {
        private static void Main(string[] args)
        {
            const int x0 = 0;
            const int y0 = 0;
            const double height = 15.0; // height of the mirror in mm
            const double radius = 40.0; // radius in mm
            const double baseAngle = 2;

            var faceOrder = new[] {3, 6, 1, 8, 4, 5, 2, 7}; // for better balance the faces are

            for (var i = 0; i < 8; i++)
            {
                var phi0 = i*45.0*Math.PI/180.0;
                var phi1 = (i + 1)*45.0*Math.PI/180.0;
                
                var angle = faceOrder[i] + baseAngle;

                var distanceFromCenter = radius - height*Math.Sin(angle*Math.PI/180.0);

                Console.WriteLine("{0}-{1}\t{2:0.000}", i, angle, distanceFromCenter);
                Console.WriteLine("{0:0.000}\t{1:0.000}", x0 + distanceFromCenter*Math.Cos(phi0), y0 + distanceFromCenter*Math.Sin(phi0));
                Console.WriteLine("{0:0.000}\t{1:0.000}", x0 + distanceFromCenter*Math.Cos(phi1), y0 + distanceFromCenter*Math.Sin(phi1));
                Console.WriteLine();
            }
            Console.WriteLine("Press any key to exit");
            Console.ReadKey();
        }
    }
}
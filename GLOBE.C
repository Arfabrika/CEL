/* FILE NAME: T35GLOBE.C
 * PROGRAMMER: FABRIKA ARTEM (AF5)
 * DATE: 05.01.2019
 * PERPOSE: WiNAPI windowed application sample
 */

#include <math.h>
#include "GLOBE.H"

HBRUSH hBr;
VEC G[N][M];

/* The create vector function
 * ARGUMENTS:
 *  - point coordinates:
 *      DOUBLE X, DOUBLE Y, DOUBLE Z;
 * RETURN:
 *  (VEC)
 */
VEC VecSet( DOUBLE X, DOUBLE Y, DOUBLE Z )
{
  VEC r = {X, Y, Z};

  return r;
} /* End of VecSet function */

/* The rotate vector to Y function
 * ARGUMENTS:
 *  - Vector:
 *      VEC V;
 *  - Angle in degrees:
 *      DOUBLE AngleD;
 * RETURN:
 *  (VEC)
 */
VEC VecRotateY( VEC V, DOUBLE AngleD )
{
  VEC r;
  DOUBLE a = D2R(AngleD), si = sin(a), co = cos(a);

  r.X = V.Z * si + V.X * co;
  r.Y = V.Y;
  r.Z = V.Z * co - V.X * si;
  return r;
} /* End of VecSet function */

/* The sphere inicializate function
 * ARGUMENTS:
 *  None
 * RETURN:
 *  None
 */
VOID GLB_Init( VOID )
{
  DOUBLE theta, phi, x, y, z;
  INT i, j;

  for (theta = 0, i = 0; i < N; i++, theta += PI / (N - 1))
    for (phi = 0, j = 0; j < M; j++, phi += 2 * PI / (M - 1))
    {
      x = R * sin(theta) * sin(phi);
      z = R * sin(theta) * cos(phi);
      y = R * cos(theta);
      G[i][j] = VecSet(x, y, z);
    }
} /* End of 'GLB_Init' function */

/* The sphere draw function
 * ARGUMENTS:
 * - work device context
 *     HDC hDC;
 * - center coordinates
 *     INT Xc, INT Yc;
 * RETURN:
 *  None
 */
VOID GLB_Draw( HDC hDC, INT W, INT H, DOUBLE Angle )
{
  INT i, j, s = 1;
  DOUBLE Wp = 0.3, Hp = 0.3, Ws = W, Hs = H, ProjDist = 0.1, xp, yp, xs, ys;
  static VEC v[N][M];
  static POINT pts[N][M];

  if (Ws >= Hs)
    Wp = s * Ws / Hs, Hp = s;
  else
    Hp = s * Hs / Ws, Wp = s;

  for (i = 0; i < N; i++)
    for (j = 0; j < M; j++)
    {
      v[i][j] = VecRotateY(G[i][j], Angle);
      v[i][j].Z -= 400;
    }

  for (i = 0; i < N; i++)
    for (j = 0; j < M; j++)
    {
      xp = v[i][j].X * ProjDist / -v[i][j].Z;
      yp = v[i][j].Y * ProjDist / -v[i][j].Z;

      xs = W / 2 + xp * W / Wp;
      ys = H / 2 - yp * H / Hp;

      pts[i][j].x = xs;
      pts[i][j].y = ys;

      Ellipse(hDC, pts[i][j].x - s, pts[i][j].y - s, pts[i][j].x + s, pts[i][j].y + s);
    }
    
    /* By lines */
    for (i = 0; i < N; i++)
    {
      MoveToEx(hDC, pts[i][0].x, pts[i][0].y, 0);
      for (j = 1; j < M; j++)
        LineTo(hDC, pts[i][j].x, pts[i][j].y);
    }
    for (j = 1; j < M; j++)
    {
      MoveToEx(hDC, pts[0][j].x, pts[0][j].y, 0);
      for (i = 0; i < N; i++)
        LineTo(hDC, pts[i][j].x, pts[i][j].y);
    }
#if 0
    /* By facets */
    for (i = 0; i < N; i++)
      for (j = 1; j < M; j++)
      {
         POINT pts1[4];

         pts1[0] = pts[i][j];
         pts1[1] = pts[i][j + 1];
         pts1[2] = pts[i + 1][j + 1];
         pts1[3] = pts[i + 1][j];
         if (((pts1[0].x - pts1[1].x) * (pts1[0].y + pts1[1].y) +
              (pts1[1].x - pts1[2].x) * (pts1[1].y + pts1[2].y) +
              (pts1[2].x - pts1[3].x) * (pts1[2].y + pts1[3].y) +
              (pts1[3].x - pts1[0].x) * (pts1[3].y + pts1[0].y)) < 0)
           Polygon(hDC, pts1, 4);
      }
#endif /* 0 */
} /* End of 'GLB_Drawt' function */

/* END OF 'GLOBE.C' FILE */

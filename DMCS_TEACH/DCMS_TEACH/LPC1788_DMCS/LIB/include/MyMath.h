long SetArcPoint(double Xbegin,double Ybegin,double Zbegin,
		 double Xmid,double Ymid,double Zmid,
		 double Xend,double Yend,double Zend,
		 double *ArcLen);

void GetArcPoint(long Count,double *PointDat);


double Calc_Lenght(double X1,double Y1,double X2,double Y2);
void AbsPianzhuan(double *X,double *Y, double Xo, double Yo, double Jd);
void AbsPianzhuan_L(double *X,double *Y, double Xo, double Yo, double Jd,double L);
double Calc_Angle(double X, double Y, double Rx, double Ry);
long Calc_TPCenter(double Xs,double Ys,double Xz,double Yz,double Xl,double Yl,double *Xo,double *Yo);

void RelPianzhuan(double *X,double *Y, double Xo, double Yo, double Jd);

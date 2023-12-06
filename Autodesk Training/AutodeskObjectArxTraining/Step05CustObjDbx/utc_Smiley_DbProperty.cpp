//Implementation for all get/set properties for utc_smiley

#include "StdAfx.h"
#include "utc_Smiley.h"


//properties
AcCmEntityColor utc_Smiley::faceColor() const
{
	assertReadEnabled();
	return m_facecolor;
}

void utc_Smiley::setFaceColor(const AcCmEntityColor& color)
{
	assertWriteEnabled();
	m_facecolor = color;
}

AcGeVector3d utc_Smiley::normal() const
{
	assertReadEnabled();
	return m_normal;
}

void utc_Smiley::setNormal(const AcGeVector3d v)
{
	assertWriteEnabled();
	m_normal = v;
}

AcGePoint3d utc_Smiley::center() const
{
	assertReadEnabled();
	return m_facecircle.center();
}

void utc_Smiley::setCenter(const AcGePoint3d c)
{

	assertWriteEnabled();
	m_moutharc.translateBy(c - m_facecircle.center());
	m_facecircle.setCenter(c);
	recordGraphicsModified();
}

double utc_Smiley::radius() const
{
	assertReadEnabled();
	return m_facecircle.radius();
}

void utc_Smiley::setRadius(const double r)
{
	assertWriteEnabled();
	m_facecircle.setRadius(r);
	recordGraphicsModified();
}

double utc_Smiley::eyesApart() const
{
	assertReadEnabled();
	return m_eyesapart;
}

void utc_Smiley::setEyesApart(const double a)
{
	assertWriteEnabled();
	m_eyesapart = a;
	recordGraphicsModified();

}

double utc_Smiley::eyesHeight() const
{
	assertReadEnabled();
	return m_eyesheight;
}

void utc_Smiley::setEyesHeight(const double h)
{
	assertWriteEnabled();
	m_eyesheight = h;
	recordGraphicsModified();
}

double utc_Smiley::eyeSize() const
{
	assertReadEnabled();
	return m_eyesize;
}

void utc_Smiley::setEyeSize(const double s)
{
	assertWriteEnabled();
	m_eyesize = s;
	recordGraphicsModified();
}

AcGePoint3d utc_Smiley::leftEyeCenter() const
{
	assertReadEnabled();
	AcGeVector3d offset(-m_eyesapart / 2, m_eyesheight, 0);
	return m_facecircle.center() + offset;
}

AcGePoint3d utc_Smiley::rightEyeCenter() const
{
	assertReadEnabled();
	AcGeVector3d offset(m_eyesapart / 2, m_eyesheight, 0);
	return m_facecircle.center() + offset;
}

double utc_Smiley::mouthRadius() const
{
	assertReadEnabled();
	return m_moutharc.radius();
}

AcGePoint3d utc_Smiley::mouthCenter() const
{
	assertReadEnabled();
	return m_moutharc.center();
}

AcGePoint3d utc_Smiley::mouthLeft() const
{
	assertReadEnabled();
	return m_moutharc.startPoint();
}

AcGePoint3d utc_Smiley::mouthRight() const
{
	assertReadEnabled();
	return m_moutharc.endPoint();
}

AcGePoint3d utc_Smiley::mouthBottom() const
{
	assertReadEnabled();							
	int countIntersect;								
	AcGePoint3d faceBottom(center() - AcGeVector3d(0, radius(), 0)),
		FirstIntersect, SecondIntersect;
	AcGeLine3d  line(mouthCenter(), faceBottom);

	m_moutharc.intersectWith(line, countIntersect, FirstIntersect, SecondIntersect);
	return FirstIntersect;
}

void utc_Smiley::setMouth(const AcGePoint3d& left, const AcGePoint3d& bottom, const AcGePoint3d& right)
{
	assertWriteEnabled();
	AcGePoint3d realLeft(left), realBottom(bottom), realRight(right);

	double topY = center().y + m_eyesheight - m_eyesize;
	double diff = 0.0;								// Mouth must be under eyes always

	if ((left.y - topY) > diff) {
		diff = left.y - topY;
	}
	if ((bottom.y - topY) > diff) {
		diff = bottom.y - topY;
	}
	if ((right.y - topY) > diff) {
		diff = right.y - topY;
	}

	AcGeVector3d vec(0, diff, 0);
	m_moutharc.set(realLeft - vec, realBottom - vec, realRight - vec);
	recordGraphicsModified();


}

void utc_Smiley::moveMouthToPoint(const AcGePoint3d point)
{
}


//validate radius
void utc_Smiley::ensureRadiusMouth()
{
	double d;
	AcGePoint3d cen(center());
	if ((d = cen.distanceTo(mouthLeft())) > radius() / 1.1) setRadius(1.1 * d);
	if ((d = cen.distanceTo(mouthRight())) > radius() / 1.1) setRadius(1.1 * d);
	if ((d = cen.distanceTo(mouthBottom())) > radius() / 1.1) setRadius(1.1 * d);
}

void utc_Smiley::ensureRadiusEyes()
{
	double d = center().distanceTo(leftEyeCenter()) + eyeSize();
	if (d > radius() / 1.1) setRadius(1.1 * d);
}
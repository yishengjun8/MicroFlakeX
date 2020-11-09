#include "pch.h"
#include "MfxLowPart.h"

std::wstring MicroFlakeX::MfxWords::Global_FontName = L"Consolas";
int MicroFlakeX::MfxWords::Global_WordsSize = 14;
int MicroFlakeX::MfxWords::Global_LineSize = 6;

MicroFlakeX::MfxWords::MfxWords(Gdiplus::Graphics* myGraphics)
{
	words = L"<Sample Words>\n<__Ê¾ÀýÎÄ×Ö__>\n<Sample Words>";
	wordsFontName = Global_FontName;
	wordsSize = Global_WordsSize;
	wordsRectF = Gdiplus::RectF(0, 0, 160, 90);
	wordsOffset = Gdiplus::PointF(Global_LineSize / 4, Global_LineSize / 2);
	wordsFormatXY = MFXWORDS_FORMATX_NEAR | MFXWORDS_FORMATY_NEAR;
	lineSize = Global_LineSize;

	myGraphics = myGraphics;

	wordsFont = new Gdiplus::Font(wordsFontName.c_str(), wordsSize);
	wordsFormat.SetAlignment(Gdiplus::StringAlignmentNear);

	wordsColor = Gdiplus::Color::Black;//ÎÄ×ÖÑÕÉ«
	lineColor = Gdiplus::Color::Green;//±ß¿òÑÕÉ«
	backColor = Gdiplus::Color::Gray;//±³¾°ÑÕÉ«

	worldsBrush = new Gdiplus::SolidBrush(wordsColor);//ÎÄ×Ö»­Ë¢
	linePen = new Gdiplus::Pen(lineColor, lineSize);//±ß¿ò»­±Ê
	backBrush = new Gdiplus::SolidBrush(backColor);//±³¾°»­Ë¢
}

MicroFlakeX::MfxWords::~MfxWords()
{
	delete wordsFont;

	delete worldsBrush;
	delete linePen;
	delete backBrush;
}

std::wstring MicroFlakeX::MfxWords::SetGlobalFont(std::wstring g_wFont)
{
	std::wstring retFontName = Global_FontName;
	Global_FontName = g_wFont;
	return retFontName;
}

std::wstring MicroFlakeX::MfxWords::GetGlobalFont()
{
	return Global_FontName;
}

int MicroFlakeX::MfxWords::SetGlobalWordsSize(int g_wSize)
{
	int retSize = Global_WordsSize;
	Global_WordsSize = g_wSize;
	return retSize;
}

int MicroFlakeX::MfxWords::GetGlobalWordsSize()
{
	return Global_WordsSize;
}

int MicroFlakeX::MfxWords::SetGlobalLineSize(int g_lSize)
{
	int retSize = Global_LineSize;
	Global_LineSize = g_lSize;
	return retSize;
}

int MicroFlakeX::MfxWords::GetGlobalLineSize()
{
	return Global_LineSize;
}

std::wstring MicroFlakeX::MfxWords::SetWords(std::wstring wStr)
{
	std::wstring retWords = words;
	words = wStr;
	return retWords;
}

std::wstring MicroFlakeX::MfxWords::GetWords()
{
	return std::wstring();
}

std::wstring MicroFlakeX::MfxWords::SetWordsFont(std::wstring wFont)
{
	Gdiplus::Font* tFont = nullptr;
	tFont = new Gdiplus::Font(wFont.c_str(), wordsSize);
	if (tFont == nullptr)
	{
		return std::wstring{L"Font Error"};
	}

	std::wstring retStr = wordsFontName;
	wordsFontName = wFont;
	delete wordsFont;
	wordsFont = tFont;
	return retStr;
}

std::wstring MicroFlakeX::MfxWords::GetWordsFont()
{
	return wordsFontName;
}


int MicroFlakeX::MfxWords::SetWordsSize(int wSize)
{
	if (wSize <= 0)
	{
		return -1;
	}
	Gdiplus::Font* tFont = nullptr;
	tFont = new Gdiplus::Font(wordsFontName.c_str(), wordsSize);
	if (tFont == nullptr)
	{
		return -1;
	}

	int retSize = wordsSize;
	wordsSize = wSize;
	delete wordsFont;
	wordsFont = tFont;
	return retSize;
}

int MicroFlakeX::MfxWords::GetWordsSize()
{
	return wordsSize;
}

int MicroFlakeX::MfxWords::SetLineSize(int lSize)
{
	if (linePen->SetWidth(lSize) != Gdiplus::Ok)
	{
		return -1;
	}
	int retSize = lineSize;
	lineSize = lSize;

	return retSize;
}

int MicroFlakeX::MfxWords::GetLineSize()
{
	return lineSize;
}

Gdiplus::PointF MicroFlakeX::MfxWords::SetWordsPointF(Gdiplus::PointF wPointF)
{
	Gdiplus::PointF retPointF(wordsRectF.X, wordsRectF.Y);
	wordsRectF.X = wPointF.X;
	wordsRectF.Y = wPointF.Y;
	return retPointF;
}

Gdiplus::PointF MicroFlakeX::MfxWords::GetWordsPointF()
{
	Gdiplus::PointF retPointF(wordsRectF.X, wordsRectF.Y);
	return retPointF;
}

Gdiplus::SizeF MicroFlakeX::MfxWords::SetWordsSizeF(Gdiplus::SizeF wSizeF)
{
	Gdiplus::SizeF retSizeF(wordsRectF.Width, wordsRectF.Height);
	wordsRectF.Width = wSizeF.Width;
	wordsRectF.Height = wSizeF.Height;
	return retSizeF;
}

Gdiplus::SizeF MicroFlakeX::MfxWords::GetWordsSizeF()
{
	Gdiplus::SizeF retSizeF(wordsRectF.Width, wordsRectF.Height);
	return retSizeF;
}

Gdiplus::RectF MicroFlakeX::MfxWords::GetWordsRectF()
{
	return wordsRectF;
}

Gdiplus::PointF MicroFlakeX::MfxWords::SetWordsOffset(Gdiplus::PointF wOffset)
{
	Gdiplus::PointF retOffset = wordsOffset;
	wordsOffset = wOffset;
	return retOffset;
}

Gdiplus::PointF MicroFlakeX::MfxWords::GetWordsOffset()
{
	return wordsOffset;
}

MicroFlakeX::MFXWORDS_FORMAT MicroFlakeX::MfxWords::SetWordsFormat(MFXWORDS_FORMAT wFormat)
{
	wordsFormatXY = wFormat;

	wordsFormatXY& MFXWORDS_FORMATX_NEAR ? wordsFormat.SetAlignment(Gdiplus::StringAlignmentNear) : 0;
	wordsFormatXY& MFXWORDS_FORMATX_CENTER ? wordsFormat.SetAlignment(Gdiplus::StringAlignmentCenter) : 0;
	wordsFormatXY& MFXWORDS_FORMATX_FAR ? wordsFormat.SetAlignment(Gdiplus::StringAlignmentFar) : 0;

	return wordsFormatXY;
}

MicroFlakeX::MFXWORDS_FORMAT MicroFlakeX::MfxWords::GetWordsFormat()
{
	return wordsFormatXY;
}

Gdiplus::Color MicroFlakeX::MfxWords::SetWordsColor(Gdiplus::Color wColor)
{
	if (worldsBrush->SetColor(wColor) != Gdiplus::Ok)
	{
		return Gdiplus::Color(0, 0, 0, 0);
	}
	Gdiplus::Color retColor(wordsColor);
	wordsColor = wColor;
	return retColor;
}

Gdiplus::Color MicroFlakeX::MfxWords::GetWordsColor()
{
	return wordsColor;
}

Gdiplus::Color MicroFlakeX::MfxWords::SetLineColor(Gdiplus::Color lColor)
{
	if (linePen->SetColor(lColor) != Gdiplus::Ok)
	{
		return Gdiplus::Color(0, 0, 0, 0);
	}
	Gdiplus::Color retColor(lineColor);
	lineColor = lColor;
	return retColor;
}

Gdiplus::Color MicroFlakeX::MfxWords::GetLineColor()
{
	return lineColor;
}

Gdiplus::Color MicroFlakeX::MfxWords::SetBackColor(Gdiplus::Color bColor)
{
	if (backBrush->SetColor(bColor) != Gdiplus::Ok)
	{
		return Gdiplus::Color(0, 0, 0, 0);
	}
	Gdiplus::Color retColor(backColor);
	backColor = bColor;
	return retColor;
}

Gdiplus::Color MicroFlakeX::MfxWords::GetBackColor()
{
	return backColor;
}

BOOL MicroFlakeX::MfxWords::Contains(Gdiplus::PointF ifPointF)
{
	return wordsRectF.Contains(ifPointF);
}

Gdiplus::SizeF MicroFlakeX::MfxWords::OffsetWordsSizeF(Gdiplus::SizeF wSizeF)
{
	Gdiplus::SizeF retSizeF(wordsRectF.Width, wordsRectF.Height);
	retSizeF = retSizeF + wSizeF;
	wordsRectF.Width = retSizeF.Width;
	wordsRectF.Height = retSizeF.Height;
	return retSizeF;
}

Gdiplus::Status MicroFlakeX::MfxWords::Draw(MFXWORDS_SHOW_TYPE wType)
{
	Gdiplus::Status retStatus(Gdiplus::Ok);
	if (wType & MFXWORDS_SHOW_TYPE_FILL)
	{
		retStatus = myGraphics->FillRectangle(backBrush, wordsRectF);
	}

	if (retStatus != Gdiplus::Ok)
	{
		return retStatus;
	}

	retStatus = myGraphics->DrawString(
		words.c_str(), words.length(),
		wordsFont,
		Gdiplus::RectF(wordsRectF.X, wordsRectF.Y, wordsRectF.Width, wordsRectF.Height),
		&wordsFormat,
		worldsBrush);

	if (retStatus != Gdiplus::Ok)
	{
		return retStatus;
	}

	if (wType & MFXWORDS_SHOW_TYPE_LINE)
	{
		retStatus = myGraphics->DrawRectangle(linePen, wordsRectF);
	}
	return retStatus;
}
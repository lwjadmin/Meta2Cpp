#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

namespace lwj
{
    //class XLWorkBook
    //{
    //public:
    //    string FileName;
    //    vector<XLSheet> XLSheets;
    //    XLWorkBook()
    //    {
    //        FileName = "";
    //    }
    //    void CreateXLWorkBook(string InFileName)
    //    {
    //        FileName = InFileName;
    //    }
    //};
    //class XLSheet
    //{
    //public:
    //    string SheetName;
    //    XLCell XLCells;
    //    XLSheet()
    //    {
    //        SheetName = "Sheet1";
    //    }
    //    XLSheet(string InSheetName)
    //    {
    //        SheetName = InSheetName;
    //    }
    //};
    //class XLCell
    //{
    //public:
    //    int* Cells;
    //    XLCell()
    //    {
    //        Cells = new int[512 * 512];
    //        memset(Cells, 0, sizeof(int) * 512 * 512);
    //    }
    //    int Get(int Rows, int Cols)
    //    {
    //        return Cells[Rows * 512 + Cols];
    //    }
    //    void Set(int Rows, int Cols, int value)
    //    {
    //        Cells[Rows * 512 + Cols] = value;
    //    }
    //    ~XLCell()
    //    {
    //        delete[] Cells;
    //    }
    //};
}
/*---------------------------------------------------
namespace lecture
{
    class Excel
    {
    public:
        Excel();
        vector<Sheet> workbooks;
    };

    class Sheet
    {
    public:
        Sheet();

        map< Coordinate, Cell> Cells;
        void Insert(char Row, int Column, Cell Data)
        {
            Cells[Coordinate(Row, Column)] = Data;
        }
    };

    class Coordinate
    {
    public:
        int Column;
        char Row;
        Coordinate()
        {
            Column = 0;
            Row = 0;
        }
        Coordinate(char InRow, int InColumn)
        {
            Row = InRow;
            Column = InColumn;
        }
    };

    class Cell
    {
    public:
        Cell()
        {
            Text = "";
            BackgroundColor = 0;
            FontColor = 0;
            TextAlignment = 0;
            VerticalAlignment = 0;
        }
        Cell
        (
            string InText,
            int InBackgroundColor,
            int InFontColor,
            int InTextAlignment,
            int InVerticalAlignment
        )
        {
            Text = InText;
            BackgroundColor = InBackgroundColor;
            FontColor = InFontColor;
            TextAlignment = InTextAlignment;
            VerticalAlignment = InVerticalAlignment;
        }

        string Text;
        int BackgroundColor;
        int FontColor;
        int TextAlignment;
        int VerticalAlignment;
    };
}
---------------------------------------------------*/
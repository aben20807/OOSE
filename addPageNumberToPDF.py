#!/usr/bin/env python3
# -*- coding: utf-8 -*-

helpDoc = '''
Add Page Number to PDF file with Python
Python 给 PDF 添加 页码
usage:
    python addPageNumberToPDF.py [PDF path]
require:
    pip install reportlab pypdf2
    Support both Python2/3, But more recommend Python3
tips:
    * output file will save atoutputDirPDF path]_page.pdf
    * only support A4 size PDF
    * tested on Python2/Python3@ubuntu
    * more large size of PDF require more RAM
    * if segmentation fault, plaese try use Python 3
    * if generate PDF document is damaged, plaese try use Python 3
Author:
    Lei Yang (ylxx@live.com)
GitHub:
    https://gist.github.com/DIYer22/b9ede6b5b96109788a47973649645c1f
'''
print(helpDoc)

import reportlab
from reportlab.lib.units import mm
from reportlab.pdfgen import canvas

from PyPDF2 import PdfFileWriter, PdfFileReader

def createPagePdf(num, tmp):
    c = canvas.Canvas(tmp)
    for i in range(1,num+1):
        c.drawString((210//2)*mm, (4)*mm, str(i))
        c.showPage()
    c.save()
    return
    with open(tmp, 'rb') as f:
        pdf = PdfFileReader(f)
        layer = pdf.getPage(0)
        return layer


if __name__ == "__main__":
    pass
    import sys,os
    path = 'MLDS17f.pdf'
    #    path = '1.pdf'
    if len(sys.argv) == 1:
        if not os.path.isfile(path):
            sys.exit(1)
    else:
        path = sys.argv[1]
    base = os.path.basename(path)


    tmp = "__tmp.pdf"

    batch = 10
    batch = 0
    output = PdfFileWriter()
    outputDir = "./"
    with open(path, 'rb') as f:
        pdf = PdfFileReader(f,strict=False)
        n = pdf.getNumPages()
        if batch == 0:
            batch = -n
        createPagePdf(n,tmp)
        if not os.path.isdir(outputDir):
            os.mkdir(outputDir)
        with open(tmp, 'rb') as ftmp:
            numberPdf = PdfFileReader(ftmp)
            for p in range(n):
                if not p%batch and p:
                    newpath = path.replace(base, outputDir+ base[:-4] + '_paged' + path[-4:])
                    with open(newpath, 'wb') as f:
                        output.write(f)
                    output = PdfFileWriter()
#                sys.stdout.write('\rpage: %d of %d'%(p, n))
                print('page: %d of %d'%(p, n))
                page = pdf.getPage(p)
                numberLayer = numberPdf.getPage(p)

                page.mergePage(numberLayer)
                output.addPage(page)
            if output.getNumPages():
                newpath = path.replace(base, outputDir + base[:-4] + '_paged'  + path[-4:])
                with open(newpath, 'wb') as f:
                    output.write(f)

        os.remove(tmp)
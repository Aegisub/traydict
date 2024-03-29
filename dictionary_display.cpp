// Copyright (c) 2007, Rodrigo Braz Monteiro
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//   * Redistributions of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//   * Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//   * Neither the name of the TrayDict Group nor the names of its contributors
//     may be used to endorse or promote products derived from this software
//     without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// -----------------------------------------------------------------------------
//
// TRAYDICT
//
// Website: http://aegisub.cellosoft.com
// Contact: mailto:zeratul@cellosoft.com
//

///////////
// Headers
#include "dictionary_display.h"
#include "main.h"
#include "../aegisub/text_file_reader.h"


///////////////
// Constructor
DictionaryDisplay::DictionaryDisplay(wxWindow *parent)
//: IEHtmlWin(parent,-1)
: GeckoDisplay(parent)
{
}


/////////////////
// Print results
void DictionaryDisplay::PrintResults(const ResultSet &results)
{
	// Colours
	wchar_t col[][8] = {L"#FFFFFF",L"#FEFAED"};

	// Go through each result
	AppendText(_T("<table cellpadding='2' cellspacing='0' border='0' leftmargin='0' topmargin='0' marginwidth='0' marginheight='0'>"));
	int i = 0;
	for (std::list<SearchResult>::const_iterator cur=results.results.begin();cur!=results.results.end();cur++) {
		// Get entry
		DictEntry *entry = (*cur).entry;

		// Generate row string
		wxString row = wxString::Format(_T("<tr bgcolor='%s'>"),col[(i/3) % 2]);
		row += _T("<td>") + entry->kanji + _T("</td>");
		row += _T("<td>") + entry->kana + _T(" </td>");
		row += _T("<td>") + Dictionary::kanatable.KanaToRomaji(entry->kana) + _T(" </td>");
		row += _T("<td>") + entry->english + _T("</td>");
		row += _T("</tr>");

		// Append string to page
		AppendText(row);
		i++;
	}
	AppendText(_T("</table>"));
}


/////////////////
// Start results
void DictionaryDisplay::ResultsStart()
{
	Freeze();

	// Get stylesheet path
	wxString stylesheet;
	TextFileReader styleFile(TrayDict::folderName + _T("traydict.css"));
	while (styleFile.HasMoreLines()) {
		stylesheet += styleFile.ReadLineFromFile() + _T("\n");
	}
	stylesheet = _T("");

	// Insert header
	SetText(_T(""));
	AppendText(wxString::Format(_T("<html><head><style>%s</style><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"/></head><body>"),stylesheet.c_str()));
}


/////////////////////////
// Done printing results
void DictionaryDisplay::ResultsDone()
{
	AppendText(_T("</body></html>"));
	//OpenURL(_T("about:blank"));
	//LoadData(data);
	Thaw();
	SetFocus();
}

void DictionaryDisplay::SetText(wxString text) {
	data = text;
}
void DictionaryDisplay::AppendText(wxString text) {
	data += text;
}

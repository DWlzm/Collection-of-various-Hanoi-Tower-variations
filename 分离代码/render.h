VOID SetColor(UINT uFore,UINT uBack) {
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle,uFore+uBack*0x10);
}
VOID SetTitle(LPCSTR lpTitle) {
	SetConsoleTitle(lpTitle);
}
void render()
{
	 SetTitle("Hanoi�����ӻ���ʾ����");
}
//�������ع�꺯��
void HideCursor()
{
    CONSOLE_CURSOR_INFO cursor;    
    cursor.bVisible = FALSE;    
    cursor.dwSize = sizeof(cursor);    
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);    
    SetConsoleCursorInfo(handle, &cursor);
}



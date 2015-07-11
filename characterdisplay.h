/*!
 ********************************************************************
 * \file
 * \author
 * \version
 * \date
 * \brief
 *
 ********************************************************************
 */
#ifndef CHARACTERDISPLAY_H
#define CHARACTERDISPLAY_H

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>
#include <QTimer>
#include <QMouseEvent>
#include <QPainter>

//!
struct LCFHeader{
	unsigned short FileHeader;// LF
	unsigned short FontTableSize;// 128 or 256
	unsigned short VerticalFontSize;// 4 - 32
	unsigned short HorisontalFontSize;// 4 - 32
};

enum DisplayColors{
	BACKGROUNG,
	FRAME,
	CHARACTER,
	CHAR_GRID,
	SELECTED_CHAR,
	SELECT_FRAME
};

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
class CharacterDisplay : public QWidget
{
    Q_OBJECT
public:
	explicit CharacterDisplay(QWidget *parent = 0);

	QSize minimumSizeHint() const {
		return QSize(n_char * 18 + 20, n_str * 27 + 20); }

	QSize sizeHint() const {
		return QSize(n_char * 18 + 20, n_str * 27 + 20); }

	void set_read_only(bool state) {read_only = state;}

	void setDispalySize(int col, int row) {
		delete display_str;n_char = col;n_str = row;
		display_str = new char[col * row + 1];
		display_str[n_str * n_char] = 0x00;
		setMinimumSize(n_char * 18 + 20, n_str * 27 + 20);
		update(); }

	void setDispalyColors(QColor bg, QColor cbg, QColor cfg, QColor f){
		bg_color = bg; cbg_color = cbg; cfg_color = cfg; frame_color = f;
		update(); }

	void setDispalyColors(DisplayColors colors, QColor color);

	void set_blink_interval(int interval){cursor_blink_interval = interval;}

	void write_string(char *str){
		for(int i = 0; i < 32; i++)
			display_str[i] = str[i];
		update(); }

	void clear_screen(void){
		for(int i = 0; i < n_char*n_str;i++)
			display_str[i] = ' ';
		update();
	}

signals:
	void changed(char *str);// �������� ������

	void clicked(int ch); // ������� � ������

public slots:
	void setPen(const QPen &pen){this->pen = pen;update();}

private slots:
	void blink_cursor(void);

protected:
	void paintEvent(QPaintEvent *enent);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);

private:
	char * display_str;			// ������ �������� ��������� �� �����
	int n_char;					// ���������� �������� � ������
	int n_str;					// ���������� ����� ������
	int selected_char;			// ���������� ������
	int selected_str;			// ���������� ������
	int cursor_char;			// � ����� ������� ��������� ������
	int cursor_str;				// � ����� ������ ��������� ������
	int cursor_blink_interval;	// �������� �������� �������
	bool cursor_on;				// ����� �������������� ������� �������
	bool cursor_state;			// = true;
	bool timer_state;			// = false;
	bool shift;					// ������ ������� ����
	bool read_only;				// ������ ������
	int character;				// ������� ������ �� ����������
	QColor bg_color;			// ���� ����
	QColor frame_color;			// ���� ����� ������
	QColor cbg_color;			// ���� ���� �������
	QColor cfg_color;			// ���� �������
	QColor bg_select_color;		// ��� ����� ���������
	QColor frame_select_color;	// ���� ����� ���������
	QPen pen;					// ����

	void move_left(void);
	void move_right(void);

	bool in_zone(int value, int min, int max){
		return (value > min) ? ((value < max) ? true : false) : false;
	}
};

#endif // CHARACTERDISPLAY_H

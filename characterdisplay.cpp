/*****************************************************************************************
 * шрифт вообще было бы не кисло выковыривать из файла.
 * файл будем называть lcf (или LCd Font)
 * и значит структура... разрисуем её полностью в characterdisplay.h
 *
 *
 *****************************************************************************************/

#include "characterdisplay.h"

const char font_ascii[128][5] =
{
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, // 00 /-/
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, // 01 /-/O
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, // 02 /-/O
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, // 03 /-/¦
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, // 04 /-/¦
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, // 05 /-/¦
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, // 06 /-/¦
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, // 07 /-/•
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, // 08 /-/•
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, // 09 /-/0
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, // 0A /-/0
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, // 0B /-/>
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, // 0C /-/+
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, // 0D /-/d
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, // 0E /-/d
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, // 0F /-/0+
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, // 10 /-/>
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, // 11 /-/<
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, // 12 /-/¦
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, // 13 /-/!
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, // 14 /-/¶
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, // 15 /-/§
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, // 16 /-/-
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, // 17 /-/¦
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, // 18 /-/^
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, // 19 /-/v
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, // 1A /-/>
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, // 1B /-/<
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, // 1C /-/L
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, // 1D /-/-
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, // 1E /-/^
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, // 1F /-/Ў+
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, // 20 'пробел'
	{ 0x00, 0x00, 0x5F, 0x00, 0x00 }, // 21 !
	{ 0x00, 0x07, 0x00, 0x07, 0x00 }, // 22 "
	{ 0x14, 0x7F, 0x14, 0x7F, 0x14 }, // 23 #
	{ 0x24, 0x2A, 0x7F, 0x2A, 0x12 }, // 24 $
	{ 0x23, 0x13, 0x08, 0x64, 0x62 }, // 25 %
	{ 0x36, 0x49, 0x55, 0x22, 0x50 }, // 26 &
	{ 0x00, 0x05, 0x03, 0x00, 0x00 }, // 27 '
	{ 0x00, 0x1C, 0x22, 0x41, 0x00 }, // 28 (
	{ 0x00, 0x41, 0x22, 0x1C, 0x00 }, // 29 )
	{ 0x14, 0x08, 0x3E, 0x08, 0x14 }, // 2A *
	{ 0x08, 0x08, 0x3E, 0x08, 0x08 }, // 2B +
	{ 0x00, 0x50, 0x30, 0x00, 0x00 }, // 2C ,
	{ 0x08, 0x08, 0x08, 0x08, 0x08 }, // 2D -
	{ 0x00, 0x60, 0x60, 0x00, 0x00 }, // 2E .
	{ 0x20, 0x10, 0x08, 0x04, 0x02 }, // 2F /+
	{ 0x3E, 0x51, 0x49, 0x45, 0x3E }, // 30 0
	{ 0x00, 0x42, 0x7F, 0x40, 0x00 }, // 31 1
	{ 0x42, 0x61, 0x51, 0x49, 0x46 }, // 32 2
	{ 0x21, 0x41, 0x45, 0x4B, 0x31 }, // 33 3
	{ 0x18, 0x14, 0x12, 0x7F, 0x10 }, // 34 4
	{ 0x27, 0x45, 0x45, 0x45, 0x39 }, // 35 5
	{ 0x3C, 0x4A, 0x49, 0x49, 0x30 }, // 36 6
	{ 0x03, 0x01, 0x71, 0x09, 0x07 }, // 37 7
	{ 0x36, 0x49, 0x49, 0x49, 0x36 }, // 38 8
	{ 0x06, 0x49, 0x49, 0x29, 0x1E }, // 39 9
	{ 0x00, 0x36, 0x36, 0x00, 0x00 }, // 3A :
	{ 0x00, 0x56, 0x36, 0x00, 0x00 }, // 3B ;
	{ 0x08, 0x14, 0x22, 0x41, 0x00 }, // 3C <
	{ 0x14, 0x14, 0x14, 0x14, 0x14 }, // 3D =
	{ 0x00, 0x41, 0x22, 0x14, 0x08 }, // 3E >
	{ 0x02, 0x01, 0x51, 0x09, 0x06 }, // 3F ?+
	{ 0x32, 0x49, 0x79, 0x41, 0x3E }, // 40 @
	{ 0x7C, 0x12, 0x11, 0x12, 0x7C }, // 41 A
	{ 0x7F, 0x49, 0x49, 0x49, 0x36 }, // 42 B
	{ 0x3E, 0x41, 0x41, 0x41, 0x22 }, // 43 C
	{ 0x7F, 0x41, 0x41, 0x41, 0x3E }, // 44 D
	{ 0x7F, 0x49, 0x49, 0x49, 0x41 }, // 45 E
	{ 0x7F, 0x09, 0x09, 0x09, 0x01 }, // 46 F
	{ 0x3E, 0x41, 0x51, 0x51, 0x32 }, // 47 G
	{ 0x7F, 0x08, 0x08, 0x08, 0x7F }, // 48 H
	{ 0x00, 0x41, 0x7F, 0x41, 0x00 }, // 49 I
	{ 0x20, 0x40, 0x41, 0x3F, 0x01 }, // 4A J
	{ 0x7F, 0x08, 0x14, 0x22, 0x41 }, // 4B K
	{ 0x7F, 0x40, 0x40, 0x40, 0x40 }, // 4C L
	{ 0x7F, 0x02, 0x04, 0x02, 0x7F }, // 4D M
	{ 0x7F, 0x04, 0x08, 0x10, 0x7F }, // 4E N
	{ 0x3E, 0x41, 0x41, 0x41, 0x3E }, // 4F O+
	{ 0x7F, 0x11, 0x11, 0x11, 0x0E }, // 50 P
	{ 0x3E, 0x41, 0x51, 0x21, 0x5E }, // 51 Q
	{ 0x7F, 0x09, 0x19, 0x29, 0x46 }, // 52 R
	{ 0x46, 0x49, 0x49, 0x49, 0x31 }, // 53 S
	{ 0x01, 0x01, 0x7F, 0x01, 0x01 }, // 54 T
	{ 0x3F, 0x40, 0x40, 0x40, 0x3F }, // 55 U
	{ 0x1F, 0x20, 0x40, 0x20, 0x1F }, // 56 V
	{ 0x3F, 0x40, 0x30, 0x40, 0x3F }, // 57 Ww
	{ 0x63, 0x14, 0x08, 0x14, 0x63 }, // 58 X
	{ 0x07, 0x08, 0x70, 0x08, 0x07 }, // 59 Y
	{ 0x61, 0x51, 0x49, 0x45, 0x43 }, // 5A Z
	{ 0x00, 0x7F, 0x41, 0x00, 0x00 }, // 5B [
	{ 0x02, 0x04, 0x08, 0x10, 0x20 }, // 5C \+
	{ 0x00, 0x00, 0x41, 0x7F, 0x00 }, // 5D ]
	{ 0x04, 0x02, 0x01, 0x02, 0x04 }, // 5E ^
	{ 0x40, 0x40, 0x40, 0x40, 0x40 }, // 5F _+
	{ 0x00, 0x01, 0x02, 0x04, 0x00 }, // 60 `
	{ 0x20, 0x54, 0x54, 0x54, 0x78 }, // 61 a
	{ 0x7F, 0x48, 0x44, 0x44, 0x38 }, // 62 b
	{ 0x38, 0x44, 0x44, 0x44, 0x28 }, // 63 c
	{ 0x38, 0x44, 0x44, 0x48, 0x7F }, // 64 d
	{ 0x38, 0x54, 0x54, 0x54, 0x58 }, // 65 e
	{ 0x08, 0x7E, 0x09, 0x01, 0x02 }, // 66 f
	{ 0x0C, 0x52, 0x52, 0x52, 0x3E }, // 67 g
	{ 0x7F, 0x08, 0x04, 0x04, 0x78 }, // 68 h
	{ 0x00, 0x44, 0x7D, 0x40, 0x00 }, // 69 i
	{ 0x20, 0x40, 0x44, 0x3D, 0x00 }, // 6A j
	{ 0x7F, 0x10, 0x28, 0x44, 0x00 }, // 6B k
	{ 0x00, 0x41, 0x7f, 0x40, 0x00 }, // 6C l
	{ 0x7C, 0x04, 0x18, 0x04, 0x78 }, // 6D m
	{ 0x7C, 0x08, 0x04, 0x04, 0x78 }, // 6E n
	{ 0x38, 0x44, 0x44, 0x44, 0x38 }, // 6F o+
	{ 0x7C, 0x14, 0x14, 0x14, 0x08 }, // 70 p
	{ 0x08, 0x14, 0x14, 0x18, 0x7C }, // 71 q
	{ 0x7C, 0x08, 0x04, 0x04, 0x08 }, // 72 r
	{ 0x48, 0x54, 0x54, 0x54, 0x24 }, // 73 s
	{ 0x04, 0x3F, 0x44, 0x40, 0x20 }, // 74 t
	{ 0x3C, 0x40, 0x40, 0x20, 0x7C }, // 75 u
	{ 0x1C, 0x20, 0x40, 0x20, 0x1C }, // 76 v
	{ 0x3C, 0x40, 0x30, 0x40, 0x3C }, // 77 w
	{ 0x44, 0x28, 0x10, 0x28, 0x44 }, // 78 x
	{ 0x0C, 0x50, 0x50, 0x50, 0x3C }, // 79 y
	{ 0x44, 0x64, 0x54, 0x4C, 0x44 }, // 7A z
	{ 0x00, 0x08, 0x36, 0x41, 0x00 }, // 7B {
	{ 0x00, 0x00, 0x7F, 0x00, 0x00 }, // 7C |
	{ 0x00, 0x41, 0x36, 0x08, 0x00 }, // 7D }
	{ 0x04, 0x02, 0x06, 0x04, 0x02 }, // 7E ~
	{ 0x78, 0x44, 0x42, 0x44, 0x78 }, // 7F ¦
};

CharacterDisplay::CharacterDisplay(QWidget *parent)
	: QWidget(parent)
	, n_char(16)
	, n_str(2)
	, selected_char(-1)
	, selected_str(-1)
	, cursor_char(-1)
	, cursor_str(-1)
	, cursor_blink_interval(500)
	, cursor_on(false)
	, cursor_state(true)
	, timer_state(false)
	, shift (false)
	, read_only(false)
	, bg_color(QColor(Qt::black))
	, frame_color(QColor(Qt::darkGreen))
	, cbg_color(QColor(32, 32, 32))
	, cfg_color(QColor(0, 255, 0))
	, bg_select_color(QColor(0, 64, 0))
	, frame_select_color(QColor(0, 96, 0))
{
	display_str = new char[n_str * n_char + 1];
	display_str[n_str * n_char] = 0x00;

	setAutoFillBackground(true);
	// Вот это разрешает событие по перемещению мыши
	setMouseTracking(true);
	// Вот это включает обработку нажатия клавиш
	setFocusPolicy(Qt::StrongFocus);
}

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
void CharacterDisplay::setDispalyColors(DisplayColors colors, QColor color)
{
	switch (colors) {
		case BACKGROUNG: bg_color = color; break;
		case FRAME: frame_color = color; break;
		case CHARACTER :cfg_color = color; break;
		case CHAR_GRID: cbg_color = color; break;
		case SELECTED_CHAR: bg_select_color = color; break;
		case SELECT_FRAME: frame_select_color = color; break;
		default:break;
	}
	update();
}

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
void CharacterDisplay::mousePressEvent(QMouseEvent *event)
{
	cursor_char = selected_char;
	cursor_str = selected_str;

	if (timer_state == false) {
		if((cursor_char != -1)&&(cursor_str != -1))
			QTimer::singleShot(cursor_blink_interval, this,
				SLOT(blink_cursor()));
		timer_state = true;
	}
	// Кликнули левой кнопкой мыши, сказали куда кликнули
	if(event->button() == Qt::LeftButton)
		emit clicked(cursor_char+cursor_str*n_char);

	update();
}

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
void CharacterDisplay::mouseMoveEvent(QMouseEvent *event)
{
	if (in_zone(event->x(), 11, n_char*18+11)) {
		selected_char = (event->x()-11)/18;
		if(in_zone(event->y(), 11, n_str*27+11))
			selected_str = (event->y()-11)/27;
		else selected_str = -1;
	} else selected_char = -1;

	update();
}

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
void CharacterDisplay::keyPressEvent(QKeyEvent *event)
{
	character = event->key();
	switch(event->key()) {
		case Qt::Key_Left:
			if (cursor_str == -1 || cursor_char == -1)
				cursor_char = 0, cursor_str = 0;
			move_left();
			break;

		case Qt::Key_Right:
			if(cursor_str == -1 || cursor_char == -1)
				cursor_str = 0;
			move_right();
			break;

		case Qt::Key_Up:
			if (cursor_str > 0)
				cursor_str--;
			break;

		case Qt::Key_Down:
			if (cursor_str < n_str-1)
				cursor_str++;
			break;

		case Qt::Key_Delete:
			display_str[cursor_char + cursor_str * n_char] = ' ';
			emit changed(display_str);
			break;

		case Qt::Key_Backspace:
			display_str[cursor_char+cursor_str*n_char - 1] = ' ';
			move_left();
			emit changed(display_str);
			break;

		case Qt::Key_Home: cursor_char = 0; break;

		case Qt::Key_End: cursor_char = n_char-1; break;

		case Qt::Key_Shift: shift = true; break;

		case Qt::Key_Enter:
			if(cursor_str < n_str - 1)
				cursor_str++;
			cursor_char = 0;
			break;

		default:break;
	}

	if ((character >= 0x20) && (character<=0x7F) && !read_only) {
		if(character >= 0x41 && character <= 0x5A)
				character |= (!shift) ? 0x20 : 0x00;
		display_str[cursor_char + cursor_str * n_char] = (char)character;
		move_right();
		emit changed(display_str);
	}
	cursor_state = true;

	update();
}

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
void CharacterDisplay::move_left()
{
	if (cursor_str > 0) {
		cursor_char--;
		if (cursor_char < 0) {
			cursor_str--;
			cursor_char = n_char - 1;
		}
	} else if (cursor_char > 0)
		cursor_char--;
}

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
void CharacterDisplay::move_right()
{
	if (cursor_str < n_str - 1) {
		cursor_char++;
		if (cursor_char >= n_char )
			cursor_char = 0, cursor_str++;

	} else if (cursor_char < n_char - 1)
		cursor_char++;
}

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
void CharacterDisplay::keyReleaseEvent(QKeyEvent *event)
{
	if(event->key() == Qt::Key_Shift) shift = false;
	character = 0;
	update();
}

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
void CharacterDisplay::blink_cursor(void)
{
	QTimer::singleShot(cursor_blink_interval, this, SLOT(blink_cursor()));
	cursor_state = !cursor_state;
	update();
}

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
void CharacterDisplay::paintEvent(QPaintEvent */*enent*/)
{
	QPainter painter(this);

	pen.setColor(Qt::black);
	painter.setPen(pen);
	painter.setBrush(Qt::black);
	painter.drawRect(0, 0, width() - 1, height() - 1);

	pen.setColor(frame_color);
	painter.setPen(pen);
	painter.setBrush(bg_color);
	painter.drawRect(4, 4, n_char * 18 + 11, n_str * 27 + 11);

	for (int s = 0; s < n_str; s++) {
		for (int c = 0; c < n_char; c++) {

			if ((selected_char == c) && (selected_str == s)) {
				pen.setColor(frame_select_color);
				painter.setPen(pen);
				painter.setBrush(bg_select_color);
				painter.drawRect(c * 18 + 11, s * 27 + 11, 15, 24);
			}

			for (unsigned int x = 0; x < 5; x++) {
				unsigned char mask = font_ascii[
					(int)display_str[((s * n_char) + c)]][x];

				mask |= ((cursor_char == c) && (cursor_str == s) &&
					cursor_state) ? 0x80 : 0x00;

				for (unsigned int y = 0; y < 8; y++) {
					pen.setColor((mask & (unsigned char)(0x01 << y)) ?
						cfg_color : cbg_color);
					painter.setPen(pen);
					painter.drawRect(x * 3 + c * 18 + 12,
						y * 3 + s * 27 + 12, 1, 1);
				}
			}
		}
	}
}



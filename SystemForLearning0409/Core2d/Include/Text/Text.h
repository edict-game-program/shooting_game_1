#pragma once

#ifndef __TEXT_H__
#define __TEXT_H__

#ifdef CORE2D_EXPORTS
#define CORE2D_TEXT_CLASS __declspec(dllexport)
#else
#define CORE2D_TEXT_CLASS __declspec(dllimport)
#endif

#include "DrawObject.h"


namespace core2d {

	/*
	* �e�L�X�g�\���N���X
	*/
	class CORE2D_TEXT_CLASS Text : public DrawObject{
	public:

		static const int cDefaultFontSize = 32; //�W�������T�C�Y

		//���_�̈ʒu
		enum class OriginPosition
		{
			Center,	//����
			Left,	//���[
			Right,	//�E�[

			Default = Center, //�����ݒ�͒������_
		};

		Text();
		explicit Text(const wchar_t* text);
		explicit Text(const char* text);

		static void destroy(Text* text);

		//�����T�C�Y�̐ݒ�
		void setFontSize(int fontSize);

		//�e�L�X�g�̐ݒ�
		void setText(const wchar_t* text);
		void setText(const char* text);

		//�\���ʒu�̐ݒ�
		void setPosition(float x, float y);

		//�\���F�̐ݒ�
		void setColor(float r, float g, float b, float a = 1.0f);

		//���_�ʒu�̐ݒ�
		void setOriginPosition(OriginPosition originPosition);

	public:
		bool render(Camera* scamera) override;

	private:
		virtual ~Text();

		//�R�s�[�̋֎~
		Text(const Text&) = delete;
		Text& operator=(const Text&) = delete;

	protected:
		class Impl;
		Impl* m_Impl;

	};
}

#endif //__TEXT_H__
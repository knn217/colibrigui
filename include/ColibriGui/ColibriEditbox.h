
#pragma once

#include "ColibriGui/ColibriRenderable.h"

COLIBRIGUI_ASSUME_NONNULL_BEGIN

namespace Colibri
{
	namespace InputType
	{
		enum InputType
		{
			Text,
			Multiline,
			Password,
			Email
		};
	}

	/** @ingroup Controls
	@class Editbox
	*/
	class Editbox : public Renderable
	{
		Label *m_label;
		Label *m_caret;
		Label *colibrigui_nullable m_secureLabel;
		/// It's in glyphs
		uint32_t m_cursorPos;

#if defined( __ANDROID__ ) || ( defined( __APPLE__ ) && defined( TARGET_OS_IPHONE ) && TARGET_OS_IPHONE )
		InputType::InputType m_inputType;
		std::string          m_textHint;
#endif

	public:
		/// When true, multiline prevents Enter key from being
		/// used for activating the Widget's PrimaryAction
		///
		/// @remark	PUBLIC MEMEBER: CAN BE EDITED DIRECTLY
		///
		/// @see	ColibriManager::isTextMultiline
		bool m_multiline;

		float m_blinkTimer;

	protected:
		void showCaret();
		bool requiresActiveUpdate() const;

		void syncSecureLabel();

	public:
		Editbox( ColibriManager *manager );

		void _initialize() colibri_override;
		void _destroy() colibri_override;

		Label *getLabel();

		/// When changing the text programatically, prefer using this function over directly
		/// modifying the Label (via getLabel) because this function will update the caret
		/// cursor position the way the user would expect.
		void setText( const char *text );

		/// Same as doing this->getLabel()->getText()
		const std::string &getText() const;

		void setState( States::States state, bool smartHighlight = true ) colibri_override;

		/// When true, text is rendered as '*' and Clipboard copy
		/// is forbidden (Clipboard paste is still allowed).
		void setSecureEntry( const bool bSecureEntry );
		bool isSecureEntry() const;

		/// Sets the input type for Android and iOS platforms. This allows backends
		/// to pass on hints for the soft keyboards.
		void setInputType( InputType::InputType inputType, const std::string &textHint );

		/// Returns what was set on setInputType. Note: On some platforms what was set
		/// in setInputType is ignored
		///
		/// If setSecureEntry( true ) was called, it has higher priority and getInputType
		/// will return InputType::Password
		InputType::InputType getInputType() const;

		/// Gets the text hint in setInputType.
		/// On most platforms the hint is discarded and always returns ""
		std::string getTextHint() const;

		void _update( float timeSinceLast ) colibri_override;

		void _setTextEdit( const char *text, int32_t selectStart,
						   int32_t selectLength ) colibri_override;
		void _setTextSpecialKey( uint32_t keyCode, uint16_t keyMod, size_t repetition ) colibri_override;
		void _setTextInput( const char *text, const bool bReplaceContents,
							const bool bCallActionListener = true ) colibri_override;

		Ogre::Vector2 _getImeLocation() colibri_override;

		bool isTextMultiline() const colibri_override;
		bool wantsTextInput() const colibri_override;

		void setTransformDirty( uint32_t dirtyReason ) colibri_final;

		void _notifyActionKeyMovement( Borders::Borders direction ) colibri_override;
	};
}  // namespace Colibri

COLIBRIGUI_ASSUME_NONNULL_END

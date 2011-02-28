
require 'simplabs/highlight'

module ProjectFilesHelper

	def hilite_code(type, string)
		Simplabs::Highlight.highlight(type, string).html_safe
	end

end


module ApplicationHelper


	def markdown(str)
		bc = BlueCloth.new(str)
		bc.to_html.html_safe
	end

  def trail(*paths)
    parts = []
    paths.unshift(['meagar.net', '/'])
    paths.each do |p|
      if p.is_a? Array
        parts << link_to(p[0], p[1])
      else
        parts << span(p)
      end
    end
    
    "<div id=\"trail\">#{parts.join(" : ")}</div>".html_safe
  end

  def file_size(bytes)
		return "#{bytes} B" if (bytes < 1000)

		return "#{(bytes / 1000.0).round(2)} KB" if (bytes < 1000000)

    "#{(bytes / 1000000.0).round(2)} MB"
  end



  def back_to(path)
    "<a href=\"#{path}\" class=\"back-link\"><span>Back</span></a>".html_safe
  end

	# encase argument in a <span> tag, mostly for graphics replacement
  def span(t)
    content_tag(:span, t).html_safe
  end

	def admin_only(&block)
		return unless current_user
		capture(&block).html_safe
	end

	def admin_opts(&block)
		return unless current_user
		output = '<div class="admin-opts">'.html_safe
		output << capture(&block)
		output.safe_concat '</div>'
	end

	def admin_link(className, *opts)
    opts.unshift "<span>#{className}</span>".html_safe
    if opts.size > 2
      opts[-1][:class] = className.downcase
      opts[-1][:title] = className.downcase
    else
      opts.push :class => className.downcase, :title => className
    end
    link_to *opts
  end

  def move_path(obj, dir) 
    url_for(:controller => obj.class.to_s.pluralize.downcase, :action => 'move', :id => obj, :direction => dir)
  end

  def move_links(obj)
    (
		admin_link('Top',    move_path(obj, :to_top)) +
		admin_link('Higher', move_path(obj, :higher)) +
		admin_link('Lower',  move_path(obj, :lower)) +
		admin_link('Bottom', move_path(obj, :to_bottom))
		).html_safe
  end

	def project_project_files_path(x)
		project_files_path x[0], x[1]
	end

	def edit_project_project_files_path(x)
		edit_project_files_path x[0], x[1]
	end

end

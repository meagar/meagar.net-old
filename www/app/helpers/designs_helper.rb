module DesignsHelper

  def thumbnail(design, url)
    ('<div class="thumbnail"><a title="' + design.title + '" class="thumbnail" href="' +
			url +  '" style="background-image:url(' + design.photo.url +
			')"><span>' + design.title + '</span></a></div>').html_safe
  end

end

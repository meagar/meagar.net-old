class Project_file < ActiveRecord::Base

  belongs_to :project

	has_attached_file :attachment

	validates_presence_of :description


#  has_attachment :storage => :file_system,
#    :max_size => 5.megabytes

#  validates_as_attachment

  acts_as_list

  def auto_content_type
    self.content_type
  end

  def auto_content_type=(value)
    self.content_type = value unless value == 'Automatic'
  end

  def source_type
    if self.content_type =~ /^source*/
      return self.content_type.sub('source/', '');
    end
  end

  def mime_type
    if self.content_type =~/^source*/
      return "text/plain"
    end
    self.content_type
  end

	def content_type
		self.attachment_content_type
	end

	def url
		self.attachment.url
	end

	def filename
		self.attachment.original_filename
	end

	def path
		self.attachment.path
	end

	def size
		self.attachment_file_size
	end

end

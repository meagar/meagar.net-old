class Design < ActiveRecord::Base

	has_attached_file :photo, :styles => { :normal => '540x200>' }, :default_style => :normal

  acts_as_list

end

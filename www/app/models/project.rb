class Project < ActiveRecord::Base

  has_many :files, :class_name => 'Project_file', :order => 'position'

  acts_as_list

	has_attached_file :icon, :styles => { :normal => '540x200>' }, :default_style => :normal

	validates_length_of :name, :within => 1..50
	validates_presence_of :brief
	validates_presence_of :description

end

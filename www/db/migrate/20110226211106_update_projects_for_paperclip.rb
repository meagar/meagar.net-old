class UpdateProjectsForPaperclip < ActiveRecord::Migration
  def self.up
		rename_column :projects, :filename, :icon_file_name
		rename_column :projects, :content_type, :icon_content_type
		rename_column :projects, :size, :icon_file_size
		
		add_column :projects, :icon_updated_at, :timestamp
  end

  def self.down
		rename_column :projects, :icon_file_name, :filename
		rename_column :projects, :icon_content_type, :content_type
		rename_column :projects, :icon_file_size, :size
		
		drop_column :projects, :icon_updated_at
  end
end

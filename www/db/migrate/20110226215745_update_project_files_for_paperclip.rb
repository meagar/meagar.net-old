class UpdateProjectFilesForPaperclip < ActiveRecord::Migration
  def self.up
		rename_column :project_files, :filename, :attachment_file_name
		rename_column :project_files, :content_type, :attachment_content_type
		rename_column :project_files, :size, :attachment_file_size
		
		add_column :project_files, :attachment_updated_at, :timestamp
  end

  def self.down
		rename_column :project_files, :filename, :attachment_file_name
		rename_column :project_files, :content_type, :attachment_content_type
		rename_column :project_files, :size, :attachment_file_size
		
		add_column :project_files, :attachment_updated_at, :timestamp
  end
end

class RenameAttachmentsToProjectFiles < ActiveRecord::Migration
  def self.up
		rename_table :attachments, :project_files	
  end

  def self.down
		rename_table :project_files, :attachments
  end
end

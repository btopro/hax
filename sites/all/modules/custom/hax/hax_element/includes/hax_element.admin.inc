<?php

/**
 * @file
 * hax_element editing UI.
 */

/**
 * UI controller.
 */
class HaxElementUIController extends EntityDefaultUIController {
  /**
   * Overrides hook_menu() defaults.
   *
   * Main reason for doing this is that parent class hook_menu() is, optimized
   * for entity type administration.
   */
  public function hook_menu() {
    // TODO: EntityDefaultUIController controller automatically adds the menu
    // to import entities, but there is a bug with this action and can not work
    // with the version of your entity_api module, track the issue # 2112755
    // https://www.drupal.org/node/2112755
    $wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : '%entity_object';

    $items = parent::hook_menu();

    // Change the overview menu type for the list of Hax Element.
    $items[$this->path]['type'] = MENU_LOCAL_TASK;

    // Replaces default entity title.
    $items[$this->path]['title'] = 'Hax Element';

    // Extend the 'add' path.
    $items[$this->path . '/add'] = array(
      'title callback' => 'entity_ui_get_action_title',
      'title arguments' => array('add', $this->entityType),
      'page callback' => 'entity_ui_bundle_add_page',
      'page arguments' => array($this->entityType),
      'access callback' => 'entity_access',
      'access arguments' => array('create', $this->entityType),
    );

    $items[$this->path . '/add/%'] = array(
      'title callback' => 'entity_ui_get_action_title',
      'title arguments' => array('add', $this->entityType, $this->id_count + 1),
      'page callback' => 'entity_ui_get_bundle_add_form',
      'page arguments' => array($this->entityType, $this->id_count + 1),
      'access callback' => 'entity_access',
      'access arguments' => array('create', $this->entityType),
    );

    $items['hax_element/' . $wildcard] = array(
      'title callback' => 'hax_element_page_title',
      'title arguments' => array(1),
      'page callback' => 'hax_element_page_view',
      'page arguments' => array(1),
      'access callback' => 'entity_access',
      'access arguments' => array('view', $this->entityType),
    );

    return $items;
  }
}

/**
 * Form callback: create or edit a Hax Element.
 */
function hax_element_form($form, &$form_state, $hax_element, $op = 'edit', $entity_type) {
  // Add the breadcrumb for the form's location.
  hax_element_set_breadcrumb();

  // Add the default field elements.
  $form['label'] = array(
    '#type' => 'textfield',
    '#title' => t('Hax Element Label'),
    '#default_value' => isset($hax_element->label) ? $hax_element->label : '',
    '#maxlength' => 255,
    '#required' => TRUE,
    '#weight' => -5,
  );

  // Add the field related form elements.
  $form_state['hax_element'] = $hax_element;
  field_attach_form('hax_element', $hax_element, $form, $form_state);

  $form['actions'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('form-actions')),
    '#weight' => 400,
  );

  // We add the form #submit array to this button along with the actual submit
  // handler to preserve any submit handlers added by a form callback_wrapper.
  $submit = array();

  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Hax Element'),
    '#submit' => $submit + array('hax_element_edit_form_submit'),
  );

  if (!empty($hax_element->label)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete Hax Element'),
      '#suffix' => l(t('Cancel'), 'admin/content/hax_element'),
      '#submit' => $submit + array('hax_element_form_submit_delete'),
      '#weight' => 45,
    );
  }

  // We append the validate handler to validate in case a form callback_wrapper
  // is used to add validate handlers earlier.
  $form['#validate'] = array('hax_element_edit_form_validate');

  return $form;
}

/**
 * Form API validate callback for the Hax Element form.
 */
function hax_element_edit_form_validate(&$form, &$form_state) {
  $hax_element = $form_state['hax_element'];

  // Notify field widgets to validate their data.
  field_attach_form_validate('hax_element', $hax_element, $form, $form_state);
}

/**
 * Form API submit callback for the Hax Element form.
 */
function hax_element_edit_form_submit(&$form, &$form_state) {
  // Save the entity and go back to the list of Hax Element.
  $hax_element = entity_ui_controller('hax_element')->entityFormSubmitBuildEntity($form, $form_state);

  // Add in created and changed times.
  $is_new_entity = $hax_element->is_new = isset($hax_element->is_new) ? $hax_element->is_new : 0;
  if ($is_new_entity) {
    $hax_element->created = time();
  }

  $hax_element->changed = time();

  $hax_element->save();

  // Send feedback message to the user.
  $message = t("Hax Element :label updated.", array(':label' => $hax_element->label));

  if ($is_new_entity) {
    $message = t("Hax Element :label created.", array(':label' => $hax_element->label));
  }

  drupal_set_message($message);

  $form_state['redirect'] = 'admin/content/hax_element';
}

/**
 * Form API submit callback for the delete button.
 */
function hax_element_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/content/hax_element/manage/' . $form_state['hax_element']->mjid . '/delete';
}

/**
 * Sets the breadcrumb for administrative Hax Element pages.
 */
function hax_element_set_breadcrumb() {
  $breadcrumb = array(
    l(t('Home'), '<front>'),
    l(t('Administration'), 'admin'),
    l(t('Content'), 'admin/content'),
    l(t('Hax Element'), 'admin/content/hax_element'),
  );

  drupal_set_breadcrumb($breadcrumb);
}
